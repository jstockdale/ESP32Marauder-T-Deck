/* FLASH SETTINGS
Board: LOLIN D32
Flash Frequency: 80MHz
Partition Scheme: Minimal SPIFFS
https://www.online-utility.org/image/convert/to/XBM
*/

#include "Setup210_LilyGo_T_Deck.h"
#include "configs.h"
#include "TouchDrvGT911.hpp"

TouchDrvGT911 touch;


#ifndef HAS_SCREEN
  #define MenuFunctions_h
  #define Display_h
#endif

#include <TFT_eSPI.h>
#include <WiFi.h>
#include "EvilPortal.h"
#include <Wire.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <Arduino.h>

#ifdef HAS_GPS
  #include "GpsInterface.h"
#endif

#include "Assets.h"
#include "WiFiScan.h"
#ifdef HAS_SD
  #include "SDInterface.h"
#endif
#include "Buffer.h"

#ifdef MARAUDER_FLIPPER
  #include "flipperLED.h"
#elif defined(XIAO_ESP32_S3)
  #include "xiaoLED.h"
#elif defined(MARAUDER_M5STICKC)
  #include "stickcLED.h"
#elif defined(HAS_NEOPIXEL_LED)
  #include "LedInterface.h"
#endif

#include "settings.h"
#include "CommandLine.h"
//#include "lang_var.h"

#ifdef HAS_BATTERY
  #include "BatteryInterface.h"
#endif

#ifdef HAS_SCREEN
  #include "Display.h"
  #include "MenuFunctions.h"
#endif

#ifdef HAS_BUTTONS
  #include "Switches.h"
  
  #if (U_BTN >= 0)
    Switches u_btn = Switches(U_BTN, 1000, U_PULL);
  #endif
  #if (D_BTN >= 0)
    Switches d_btn = Switches(D_BTN, 1000, D_PULL);
  #endif
  #if (L_BTN >= 0)
    Switches l_btn = Switches(L_BTN, 1000, L_PULL);
  #endif
  #if (R_BTN >= 0)
    Switches r_btn = Switches(R_BTN, 1000, R_PULL);
  #endif
  #if (C_BTN >= 0)
    Switches c_btn = Switches(C_BTN, 1000, C_PULL);
  #endif

#endif

WiFiScan wifi_scan_obj;
EvilPortal evil_portal_obj;
Buffer buffer_obj;
Settings settings_obj;
CommandLine cli_obj;

#ifdef HAS_GPS
  GpsInterface gps_obj;
#endif

#ifdef HAS_BATTERY
  BatteryInterface battery_obj;
#endif

#ifdef HAS_SCREEN
  Display display_obj;
  MenuFunctions menu_function_obj;
#endif

#ifdef HAS_SD
  SDInterface sd_obj;
#endif

#ifdef MARAUDER_M5STICKC
  AXP192 axp192_obj;
#endif

#ifdef MARAUDER_FLIPPER
  flipperLED flipper_led;
#elif defined(XIAO_ESP32_S3)
  xiaoLED xiao_led;
#elif defined(MARAUDER_M5STICKC)
  stickcLED stickc_led;
#else
  LedInterface led_obj;
#endif

const String PROGMEM version_number = MARAUDER_VERSION;

#ifdef HAS_NEOPIXEL_LED
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);
#endif

uint32_t currentTime  = 0;


void backlightOn() {
  #ifdef HAS_SCREEN
    #ifdef MARAUDER_MINI
      digitalWrite(TFT_BL, LOW);
    #endif
  
    #ifndef MARAUDER_MINI
      digitalWrite(TFT_BL, HIGH);
    #endif
  #endif
}

void backlightOff() {
  #ifdef HAS_SCREEN
    #ifdef MARAUDER_MINI
      digitalWrite(TFT_BL, HIGH);
    #endif
  
    #ifndef MARAUDER_MINI
      digitalWrite(TFT_BL, LOW);
    #endif
  #endif
}


void setup()
{
  #ifdef MARAUDER_M5STICKC
    axp192_obj.begin();
  #endif
  
  #ifdef HAS_SCREEN
    pinMode(TFT_BL, OUTPUT);
  #endif
  
  backlightOff();
#if BATTERY_ANALOG_ON == 1
  pinMode(BOARD_BAT_ADC, OUTPUT);
#endif
  
  // Preset SPI CS pins to avoid bus conflicts
  #ifdef HAS_SCREEN
    digitalWrite(TFT_CS, HIGH);
  #endif
  
  #ifdef HAS_SD
    pinMode(SD_CS, OUTPUT);

    delay(10);
  
    digitalWrite(SD_CS, HIGH);

    delay(10);
  #endif

  Serial.begin(115200);

  Serial.println("ESP-IDF version is: " + String(esp_get_idf_version()));

  #ifdef HAS_SCREEN
    display_obj.RunSetup();
    display_obj.tft.setTextColor(TFT_WHITE, TFT_BLACK);
  #endif

  backlightOff();

  // Draw the title screen
  /*
  #ifdef HAS_SCREEN
    #ifndef MARAUDER_MINI
      display_obj.drawJpeg("/marauder3L.jpg", 0 , 0);     // 240 x 320 image
    #else
      display_obj.drawJpeg("/marauder3L.jpg", 0, 0);
    #endif
  #endif
  */

      pinMode(BOARD_TOUCH_INT, INPUT);

    //! The board peripheral power control pin needs to be set to HIGH when using the peripheral
    pinMode(BOARD_POWERON, OUTPUT);
    digitalWrite(BOARD_POWERON, HIGH);

    Wire.begin(BOARD_I2C_SDA, BOARD_I2C_SCL);


    touch.setPins(-1, BOARD_TOUCH_INT);
    if (!touch.begin(Wire, GT911_SLAVE_ADDRESS_L)) {
        while (1) {
            Serial.println("Failed to find GT911 - check your wiring!");
            delay(1000);
        }
    }

    Serial.println("Init GT911 Sensor success!");

    // Set touch max xy
    touch.setMaxCoordinates(320, 240);

    // Set swap xy
    touch.setSwapXY(true);

    // Set mirror xy
    touch.setMirrorXY(false, true);


  #ifdef HAS_SCREEN
    Serial.println("WIDTH, HEIGHT: " + String(TFT_WIDTH) + ", " + String(TFT_HEIGHT));
    display_obj.tft.drawCentreString("ESP32 Marauder", 320/2, 240 * 0.33, 1);
    display_obj.tft.drawCentreString("JustCallMeKoko", 320/2, 240 * 0.5, 1);
    display_obj.tft.drawCentreString(display_obj.version_number, 320/2, 240 * 0.66, 1);
  #endif


  backlightOn(); // Need this

  #ifdef HAS_SCREEN
    //delay(2000);

    // Do some stealth mode stuff
    #ifdef HAS_BUTTONS
      if (c_btn.justPressed()) {
        display_obj.headless_mode = true;

        backlightOff();

        Serial.println("Headless Mode enabled");
      }
    #endif

    //display_obj.clearScreen();
  
    display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
  
    //display_obj.tft.println(text_table0[0]);
  
    //delay(2000);
  
    display_obj.tft.println("Marauder " + display_obj.version_number + "\n");
  
    display_obj.tft.println(text_table0[1]);
  #endif

  settings_obj.begin();

  #ifdef HAS_SCREEN
    display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
    display_obj.tft.drawCentreString("Initializing...", 320/2, 240 * 0.80, 1);
    display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
  #endif

  wifi_scan_obj.RunSetup();
  #ifdef HAS_SCREEN
    display_obj.tft.println(F(text_table0[2]));
  #endif

  buffer_obj = Buffer();
  #if defined(HAS_SD)
    // Do some SD stuff
    if(sd_obj.initSD()) {
      #ifdef HAS_SCREEN
        display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
        display_obj.tft.println(F(text_table0[3]));
        display_obj.tft.drawXBitmap(320/2 - 36,
                      240*.85,
                      menu_icons[STATUS_SD],
                      16,
                      16,
                      TFT_BLACK,
                      TFT_GREEN);
        //display_obj.tft.drawString("BAT", 0, 0, 1);
        display_obj.tft.drawCentreString("SD", 320/2 - 36, 240 * 0.90, 1);
        display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
      #endif
    } else {
      Serial.println(F("SD Card NOT Supported"));
      #ifdef HAS_SCREEN
        display_obj.tft.setTextColor(TFT_RED, TFT_BLACK);
        display_obj.tft.println(F(text_table0[4]));
        display_obj.tft.drawXBitmap(320/2 - 36,
                      240*.85,
                      menu_icons[STATUS_SD],
                      16,
                      16,
                      TFT_BLACK,
                      TFT_RED);
        //display_obj.tft.drawString("BAT", 0, 0, 1);
        display_obj.tft.drawCentreString("SD", 320/2 - 36, 240 * 0.90, 1);
        display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
      #endif
    }
  #endif

  Serial.println(F("Initializing..."));
  evil_portal_obj.setup();

  Serial.println(F("Initializing Battery"));
  #ifdef HAS_BATTERY
    battery_obj.RunSetup();
  #endif
  
  #ifdef HAS_SCREEN
    display_obj.tft.println(F(text_table0[5]));
  #endif

//  #ifdef HAS_SCREEN
//    display_obj.tft.println(F(text_table0[6]));
//  #endif

  #ifdef HAS_BATTERY
    battery_obj.battery_level = battery_obj.getBatteryLevel();
    display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
    display_obj.tft.println("Battery level: " + String(battery_obj.battery_level));
    display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
  #endif

  //Serial.println(F("Battery Done"));
  display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
  display_obj.tft.drawXBitmap(320/2 - 4,
                      240*.85,
                      menu_icons[STATUS_BAT],
                      16,
                      16,
                      TFT_BLACK,
                      TFT_GREEN);
  //display_obj.tft.drawString("BAT", 0, 0, 1);
  display_obj.tft.drawCentreString("BAT", 320/2 - 4, 240 * 0.90, 1);
  display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);

  // Do some LED stuff
  #ifdef T_DECK
    Serial.println(F("LED NOOP for T-Deck"));
  #elif MARAUDER_FLIPPER
    flipper_led.RunSetup();
  #elif defined(XIAO_ESP32_S3)
    xiao_led.RunSetup();
  #elif defined(MARAUDER_M5STICKC)
    stickc_led.RunSetup();
  #else
    led_obj.RunSetup();
  #endif
//
//  #ifdef HAS_SCREEN
//    display_obj.tft.println(F(text_table0[7]));
//
//    //delay(500);
//  #endif

  #ifdef HAS_GPS
    Serial.println(F("Initializing GPS"));
    gps_obj.begin();
    
    #ifdef HAS_SCREEN
      if (gps_obj.getGpsModuleStatus()) {
        display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
        display_obj.tft.drawXBitmap(320/2 + 28,
                    240*.85,
                    menu_icons[STATUS_GPS],
                    16,
                    16,
                    TFT_BLACK,
                    TFT_GREEN);
        //display_obj.tft.drawString("GPS", 0, 0, 1);
        display_obj.tft.drawCentreString("GPS", 320/2 + 28, 240 * 0.90, 1);
        display_obj.tft.println("GPS Module connected");
        display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
      }
      else {
        display_obj.tft.setTextColor(TFT_RED, TFT_BLACK);
        display_obj.tft.drawXBitmap(320/2 + 28,
                    240*.85,
                    menu_icons[STATUS_GPS],
                    16,
                    16,
                    TFT_BLACK,
                    TFT_RED);
        //display_obj.tft.drawString("GPS", 0, 0, 1);
        display_obj.tft.drawCentreString("GPS", 320/2 + 28, 240 * 0.90, 1);
        display_obj.tft.println("GPS Module failed to connect");
        display_obj.tft.setTextColor(TFT_CYAN, TFT_BLACK);
      }
    #endif
  #endif

  #ifdef HAS_SCREEN
    display_obj.tft.println(F(text_table0[8]));
  
    display_obj.tft.setTextColor(TFT_WHITE, TFT_BLACK);
  
    delay(1000);
  #endif

  #ifdef HAS_SCREEN
    menu_function_obj.RunSetup();
  #endif
  
  Serial.println(F("CLI Ready"));
  cli_obj.RunSetup();

//  display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
//  display_obj.tft.drawCentreString("MESS WITH THE BEST", 320/2, 240 * 0.90, 1);
//  display_obj.tft.drawCentreString("DIE LIKE THE REST", 320/2, 240 * 0.95, 1);
//  display_obj.tft.setTextColor(TFT_WHITE, TFT_BLACK);
}


void loop()
{
  //Serial.println(F("Starting loop..."));
  currentTime = millis();
  bool mini = false;

  #ifdef HAS_SCREEN
    display_obj.tft.setTextColor(TFT_GREEN, TFT_BLACK);
    display_obj.tft.drawString(String(currentTime), 272, TFT_HEIGHT * 0.05, 1);
    //display_obj.tft.drawString(String(battery_obj.battery_level), 272, TFT_HEIGHT * 0.1, 1);
    //display_obj.tft.drawString(String(battery_obj.battery_value), 272, TFT_HEIGHT * 0.15, 1);
  #endif

  #ifdef SCREEN_BUFFER
    mini = true;
  #endif

  #ifdef HAS_ST7789
    #ifdef HAS_BUTTONS
      if (c_btn.isHeld()) {
        if (menu_function_obj.disable_touch)
          menu_function_obj.disable_touch = false;
        else
          menu_function_obj.disable_touch = true;

        menu_function_obj.updateStatusBar();

        while (!c_btn.justReleased())
          delay(1);
      }
    #endif
  #endif

  // Update all of our objects
  /*#ifdef HAS_SCREEN
    bool do_draw = display_obj.draw_tft;
  #else
    bool do_draw = false;
  #endif*/
  //Serial.println(F("Next marker :D"));
  //if ((!do_draw) && (wifi_scan_obj.currentScanMode != ESP_UPDATE))
  //{
  cli_obj.main(currentTime);
  #ifdef HAS_SCREEN
    display_obj.main(wifi_scan_obj.currentScanMode);
  #endif
  wifi_scan_obj.main(currentTime);
  //evil_portal_obj.main(wifi_scan_obj.currentScanMode);

  #ifdef HAS_GPS
    gps_obj.main();
  #endif
  //Serial.println(F("Third marker :-)"));
  // Detect SD card
  #if defined(HAS_SD)
    sd_obj.main();
  #endif
  //Serial.println(F("may the Fourth Marker be with you"));
  // Save buffer to SD and/or serial
  buffer_obj.save();

  #ifdef HAS_BATTERY
    //Serial.println(F("Battery"));
    battery_obj.main(currentTime);
    //temp_obj.main(currentTime);
  #endif
  settings_obj.main(currentTime);
  if (((wifi_scan_obj.currentScanMode != WIFI_PACKET_MONITOR) && (wifi_scan_obj.currentScanMode != WIFI_SCAN_EAPOL)) ||
      (mini)) {
    #ifdef HAS_SCREEN
      menu_function_obj.main(currentTime);
    #endif
    //cli_obj.main(currentTime);
  }
  //Serial.println(F("LED"));
  #ifdef T_DECK
  #elif MARAUDER_FLIPPER
    flipper_led.main();
  #elif defined(XIAO_ESP32_S3)
    xiao_led.main();
  #elif defined(MARAUDER_M5STICKC)
    stickc_led.main();
  #else
    led_obj.main(currentTime);
  #endif

  //if (wifi_scan_obj.currentScanMode == OTA_UPDATE)
  //  web_obj.main();
  #ifdef HAS_SCREEN
    delay(1);
  #else
    delay(50);
  #endif
  //}
  /*else if (wifi_scan_obj.currentScanMode == ESP_UPDATE) {
    #ifdef HAS_SCREEN
      display_obj.main(wifi_scan_obj.currentScanMode);
      menu_function_obj.main(currentTime);
    #endif

    #ifdef MARAUDER_FLIPPER
      flipper_led.main();
    #elif defined(XIAO_ESP32_S3)
      xiao_led.main();
    #else
      led_obj.main(currentTime);
    #endif
    
    //cli_obj.main(currentTime);
    delay(1);
  }*/
}
