## Description
This clock is quite small, its dimensions are around 8x9x6cm. It uses ESP8266 Wemos module as a brain and two PCF8574A ICs for more pins. The clock can be powered from a 7.5V - 15V power supply due to step-up converter based on MC34063 IC. Nixie tubes are multiplexed by 14 MMBTA42 NPN transistors and 4 MMBTA92 PNP transistors. Tube voltage can be freely adjusted by turning a potentiometer. There are two microswitches in the design, I haven't found any usage for them, but you can edit the code as you wish.\
\
![alt text](https://github.com/Pastel-Industries/PastelClock/blob/main/clockfront.jpg)
## Preparing

First of all, It requires ESP8266 board package for arduino IDE (ofc)

```bash
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

There are also some libraries you need:

```
Adafruit_PCF8574.h
NTPClient.h
ESP8266WiFi.h
WiFiUdp.h
```



## Configuration

This is an explaination of available config:

```
tubetime - Time in milliseconds of lamp ignite time (Increase when tube is not glowing, decrease when flickering is visible)
updateinterval - Time between clock update
utcOffsetInSeconds - Positive offset in seconds (UTC + 2hrs(7200 seconds)
```
**Make sure that the ESP8266 is not inserted into the clock PCB while connected to the PC!**

Some tubes might flicker from time to time, that's caused by poor code optimalization (I'll fix it soon).
## Features

- `Two programmable switches` - Allows you to give them any purpose you wish
- `Low power operation` - It consumes less power than LED clock.


## Changelog
`09.02.2022` - First version upload - fixed power supply issue. BOM coming soon
## Issues

Feel free to open issues.\
I am also availablee on discord: **Pastel137#4809**

