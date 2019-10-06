# Home automation with a nodemcu v3 via Telegram Bot

## Requeriments

- Arduino IDE and/or VSCode (via arduino-vscode plugin)
- nodeMCU v3 devkit (<https://en.wikipedia.org/wiki/NodeMCU)>

## Install

- Include CTBot Library
- Follow instructions on how to create a Telegram Bot, via telegram bot BotFather or insiede CTBot library
- Rename file secrets.h_dist -> secrets.h changing the SSID, Password for Wifi and telegram Token
- Connect nodemcu to usb to computer
- Configure Arduino Board to nodeMCU v1.0
- Upload Sketch to nodeMCU

## Debug

Some information is sent to serial, so can check if the wifi is already conected
