//#include <GSM.h>
//#include <GSM3CircularBuffer.h>
//#include <GSM3IO.h>
//#include <GSM3MobileAccessProvider.h>
//#include <GSM3MobileCellManagement.h>
//#include <GSM3MobileClientProvider.h>
//#include <GSM3MobileClientService.h>
//#include <GSM3MobileDataNetworkProvider.h>
//#include <GSM3MobileMockupProvider.h>
//#include <GSM3MobileNetworkProvider.h>
//#include <GSM3MobileNetworkRegistry.h>
//#include <GSM3MobileSMSProvider.h>
//#include <GSM3MobileServerProvider.h>
//#include <GSM3MobileServerService.h>
//#include <GSM3MobileVoiceProvider.h>
//#include <GSM3SMSService.h>
//#include <GSM3ShieldV1.h>
//#include <GSM3ShieldV1AccessProvider.h>
//#include <GSM3ShieldV1BandManagement.h>
//#include <GSM3ShieldV1BaseProvider.h>
//#include <GSM3ShieldV1CellManagement.h>
//#include <GSM3ShieldV1ClientProvider.h>
//#include <GSM3ShieldV1DataNetworkProvider.h>
//#include <GSM3ShieldV1DirectModemProvider.h>
//#include <GSM3ShieldV1ModemCore.h>
//#include <GSM3ShieldV1ModemVerification.h>
//#include <GSM3ShieldV1MultiClientProvider.h>
//#include <GSM3ShieldV1MultiServerProvider.h>
//#include <GSM3ShieldV1PinManagement.h>
//#include <GSM3ShieldV1SMSProvider.h>
//#include <GSM3ShieldV1ScanNetworks.h>
//#include <GSM3ShieldV1ServerProvider.h>
//#include <GSM3ShieldV1VoiceProvider.h>
//#include <GSM3VoiceCallService.h>

#pragma once

#ifndef Display_h
#define Display_h

#include "configs.h"

#ifdef HAS_SCREEN

#include <FS.h>
#include <functional>
#include <JPEGDecoder.h>
#include <LinkedList.h>
#include <SPI.h>
#include <lvgl.h>
#include <Ticker.h>
#include "SPIFFS.h"
#include "Assets.h"

#include <TFT_eSPI.h>

// WiFi stuff
#define OTA_UPDATE 100
#define SHOW_INFO 101
#define WIFI_SCAN_OFF 0
#define WIFI_SCAN_PROBE 1
#define WIFI_SCAN_AP 2
#define WIFI_SCAN_PWN 3
#define WIFI_SCAN_EAPOL 4
#define WIFI_SCAN_DEAUTH 5
#define WIFI_SCAN_ALL 6
#define WIFI_PACKET_MONITOR 7
#define WIFI_ATTACK_BEACON_SPAM 8
#define WIFI_ATTACK_RICK_ROLL 9
#define BT_SCAN_ALL 10
#define BT_SCAN_SKIMMERS 11
#define WIFI_SCAN_ESPRESSIF 12
#define LV_JOIN_WIFI 13
#define LV_ADD_SSID 14
#define WIFI_ATTACK_BEACON_LIST 15

class Display
{
  private:
    bool SwitchOn = false;
    
    bool run_setup = true;
    
    // For the byte we read from the serial port
    byte data = 0;
    
    // A few test variables used during debugging
    boolean change_colour = 1;
    boolean selected = 1;

    void drawFrame();

    #ifdef SCREEN_BUFFER
      void scrollScreenBuffer(bool down = false);
    #endif

  public:
    Display();
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSPI_Button key[BUTTON_ARRAY_LEN];
    const String PROGMEM version_number = MARAUDER_VERSION;

    bool printing = false;
    bool loading = false;
    bool tteBar = false;
    bool draw_tft = false;
    bool exit_draw = false;
    bool headless_mode = false;

    uint8_t TOP_FIXED_AREA_2 = 48;
    uint8_t print_delay_1, print_delay_2 = 10;
    uint8_t current_banner_pos = SCREEN_WIDTH;

    LinkedList<String>* display_buffer;

    #ifdef SCREEN_BUFFER
      LinkedList<String>* screen_buffer;
    #endif

    // The initial y coordinate of the top of the buttontom text line
    uint16_t yDraw = YMAX - button_FIXED_AREA - TEXT_HEIGHT;

    // Keep track of the drawing x coordinate
    uint16_t xPos = 0;

    // The initial y coordinate of the top of the scrolling area
    uint16_t yStart = TOP_FIXED_AREA_2;
    // yArea must be a integral multiple of TEXT_HEIGHT
    uint16_t yArea = YMAX - TOP_FIXED_AREA_2 - button_FIXED_AREA;

    // We have to blank the top line each time the display is scrolled, but this takes up to 13 milliseconds
    // for a full width line, meanwhile the serial buffer may be filling... and overflowing
    // We can speed up scrolling of short text lines by just blanking the character we drew
    int blank[19]; // We keep all the strings pixel lengths to optimise the speed of the top line blanking

    void tftDrawRedOnOffButton();
    void tftDrawGreenOnOffButton();
    void tftDrawGraphObjects(byte x_scale);
    void tftDrawEapolColorKey();
    void tftDrawColorKey();
    void tftDrawXScaleButtons(byte x_scale);
    void tftDrawYScaleButtons(byte y_scale);
    void tftDrawChannelScaleButtons(int set_channel);
    void tftDrawExitScaleButtons();
    void buildBanner(String msg, int xpos);
    void clearScreen();
    void displayBuffer(bool do_clear = false);
    //void drawJpeg(const char *filename, int xpos, int ypos);
    void getTouchWhileFunction(bool pressed);
    void initScrollValues(bool tte = false);
    void jpegInfo();
    void jpegRender(int xpos, int ypos);
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void listFiles();
    void main(uint8_t scan_mode);
    void RunSetup();
    void scrollAddress(uint16_t vsp);
    int scroll_line(uint32_t color);
    void setupScrollArea(uint16_t tfa, uint16_t bfa);
    void showCenterText(String text, int y);
    void touchToExit();
    void twoPartDisplay(String center_text);
    void updateBanner(String msg);
};
#endif
#endif
