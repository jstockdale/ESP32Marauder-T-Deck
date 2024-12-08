<!---[![License: MIT](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/justcallmekoko/ESP32Marauder/blob/master/LICENSE)--->
<!---[![Gitter](https://badges.gitter.im/justcallmekoko/ESP32Marauder.png)](https://gitter.im/justcallmekoko/ESP32Marauder)--->
<!---[![Build Status](https://travis-ci.com/justcallmekoko/ESP32Marauder.svg?branch=master)](https://travis-ci.com/justcallmekoko/ESP32Marauder)--->
<!---Shields/Badges https://shields.io/--->

# ESP32 Marauder
<p align="center"><img alt="Marauder logo" src="https://github.com/justcallmekoko/ESP32Marauder/blob/master/pictures/marauder3L.jpg?raw=true" width="300"></p>
<p align="center">
  <b>A suite of WiFi/Bluetooth offensive and defensive tools for the ESP32</b>
  <br><br>
  <b>ESP32Marauder by @justcallmekoko</b>
  <br>
  <b>T-Deck port by @jstockdale</b>
  <br><br>
  <a href="https://github.com/jstockdale/ESP32Marauder/blob/master/LICENSE"><img alt="License" src="https://img.shields.io/github/license/mashape/apistatus.svg"></a>
  <br>
  <a href="https://twitter.com/intent/follow?screen_name=stockdiesel"><img src="https://img.shields.io/twitter/follow/stockdiesel?style=social&logo=twitter" alt="Twitter"></a>
  <a href="https://www.instagram.com/jstockdale"><img src="https://img.shields.io/badge/Follow%20Me-Instagram-orange" alt="Instagram"/></a>
  <br>
</p>

## Getting Started
Download the [latest release](https://github.com/justcallmekoko/ESP32Marauder/releases/latest) of the firmware.  

Check out the project [wiki](https://github.com/justcallmekoko/ESP32Marauder/wiki) for a full overview of the ESP32 Marauder

# T-Deck Edition
This is an early work in progress. It's mostly stable. Some features aren't fully working. A quick summary of the current progress is below.
```
[X] Boots
[X] Serial and CLI both work
[X] ST7899 Screen works
[X] GT911 Touch library
[X] L76K GPS works
   If it stops working / hangs during initialization, reset your device.
[X] Battery level works
[X] SD Card works
[X] Trackball works
[X] Headless menu option turns off screen (long press trackball/center button to resume)
[X] Improved serial console (non-blocking! don't user arrow keys for now lol)
[X] Moved Evil Portal files to /portals directory on SD card
--
[ ] Keyboard - TODO(jstockdale): Add keyboard support
[ ] Serial Console - TODO(jstockdale): Handle arrow keys
```
I recommend using the excellent [M5Launcher](https://github.com/bmorcelli/M5Stick-Launcher) from @bmorcelli to load this and other firmware from the sd card. This makes development easier and also allows you to quick switch between different useful firmwares (eg. Meshtastic, Marauder, and more!)

Please direct any feedback to the Issues page. This is alpha, pre-release software. And comes with no warranty of fitness or guarantees of any time. Use at your own risk. Thanks! :-)

Latest pre-release development build: [pre_alpha_ao40](https://github.com/jstockdale/ESP32Marauder-T-Deck/raw/refs/heads/t-deck/Release%20Bins/esp32_marauder_v1_0_0_20241207_tdeck_pre_alpha_ao40.bin))
