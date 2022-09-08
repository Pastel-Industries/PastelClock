## Description
This clock is quite small, its dimensions are around 8x9x6cm. It uses the ESP8266 Wemos module as a brain and two PCF8574A ICs for more pins. The clock can be powered from a 7.5V - 15V power supply due to step-up converter based on MC34063 IC. Nixie tubes are multiplexed by 14 MMBTA42 NPN transistors and 4 MMBTA92 PNP transistors. Tube voltage can be freely adjusted by turning a potentiometer. 150V works fine for my tubes. There are two microswitches in the design. I haven't found any usage for them, but you can edit the code as you wish. You can also wire a buzzer there and add an alarm clock functionality.\
\
![alt text](https://github.com/Pastel-Industries/PastelClock/blob/main/clockfront.jpg)
## Preparing

First of all, It requires ESP8266 board package for arduino IDE (ofc)

```bash
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

There are also some libraries you'll need:

```
Adafruit_PCF8574.h
NTPClient.h
ESP8266WiFi.h
WiFiUdp.h
```



## Configuration

This is an explanation of available config:

```
tubetime - Time in milliseconds of lamp ignite time (Increase when tube is not glowing, decrease when flickering is visible)
updateinterval - Time between updates from NTP server
utcOffsetInSeconds - Positive offset in seconds (UTC + 2hrs(7200 seconds))
```
**Please, flash the ESP when not inserted into PCB!**

Some tubes might flicker from time to time.
## Features

- `Two programmable I/O` - Allows you to give them any purpose you wish
- `Low power operation` - It consumes less power than a LED clock.


## Changelog
`02.09.2022` - First version upload - fixed power supply issue. BOM coming soon!\
`03.09.2022` - Optimized code, decreased amount of flickering. Improved code readability.
## Issues

Feel free to open issues.\
I am also available on discord: **Pastel137#4809**

