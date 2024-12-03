#include "BatteryInterface.h"
#include "lang_var.h"
BatteryInterface::BatteryInterface() {
  
}

void BatteryInterface::main(uint32_t currentTime) {
  if (currentTime != 0) {
    if (currentTime - initTime >= 3000) {
      //Serial.println("Checking Battery Level");
      this->initTime = millis();
      this->old_level = this->battery_level;
      int8_t new_level = this->getBatteryLevel();
      //Serial.println("Got battery level: " + String(new_level));
      this->battery_level = this->getBatteryLevel();
      if (new_level != this->old_level) {
        Serial.println(text00 + (String)new_level);
      }
    }
  }
}

void BatteryInterface::RunSetup() {
  pinMode(BOARD_BAT_ADC, INPUT);
  this->initTime = millis();
}

int8_t BatteryInterface::getBatteryLevel() {
  int bat_val = analogRead(BOARD_BAT_ADC);
  //Serial.println("Battery reading: " + String(bat_val));

  //Wire.beginTransmission(IP5306_ADDR);
  //Wire.write(0x78);
  //if (Wire.endTransmission(false) == 0 &&
  //    Wire.requestFrom(0x75, 1)) {
  //  this->i2c_supported = true;
  //  switch (Wire.read() & 0xF0) {
  //    case 0xE0: return 25;
  //    case 0xC0: return 50;
  //    case 0x80: return 75;
  //    case 0x00: return 100;
  //    default: return 0;
  //  }
  if (bat_val > 2600) {
    return 123;
  }
  else if (bat_val >= 2500) {
    return 100;
  }
  else if (bat_val > 1600) {
    return (bat_val - 1600)/(2500-1600);
  }
  else {
    return 0;
  }
}
