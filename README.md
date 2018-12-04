# ESP32 Matrix Smart Clock

This project is still in development phase. You are welcome to join.

Idea is to create Smart Clock using ESP32 and 4 piecese of 8x8 RGB NeoMatrix display (WS2812B).

Features that clock can support:
- 8x32 RGB LED display
- Clock
- Alarm
- Current Weather
- Room Temperature
- Online Radio
- 3.5mm Lautspeaker Audio
- Bluetooth Lautspeaker
- Send audio to another Bluetooth Lautspeaker
- MP3 Player (over USB or SD/microSD Card)
- Web Interface for confugration
- Mobile App (iOS and Android)
- Display custom messages
- Notifications from SmartPhone
- Custom applications (push/pull method)

## Hardware

For the board I decided to use Doit ESP32 DevKit v1 - 240MHz 320KB RAM (4MB Flash), but any other ESP32 board should work. Price for the board should be around 10€ (I had one already).

8x8 Display - I found on ebay 4 pieces for 21.28€ in total (delivery from Hong Kong). 

## Software

Software is written using PlatformIO in VisualStudio Code (arduino framework).

I decided to go with arudino framework. I think using esp-idf would be more flexible, but I do plan to make some cheeper (less features) for ESP8266 or even for ATmega 328 and arduino framework is more sutable for it.

When first time started - clock should provide own WiFi network to allow configuration over Web Inteface or over REST server (using mobile App).

## About myself

This is my first project of this scale. I'm software developer for the last 25 years, and I can call myself expert in C/C++ but with electronic I did only small hobby projects (mostly using atmel and pic microcontrollers with few sensors and LEDs).

Recently I'm using go, node.js and Angular for REST based Web Applications.
