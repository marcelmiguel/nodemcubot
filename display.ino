#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "secrets.h"
#include "peripherals.h"
#include "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADRRESS)) {
    Serial.println(F("No SSD1306 connected"));
  }
}

void printWeatherInfo() {
  char str[20];

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
    
  sprintf(str, PRINT_TEMPERATURE, temperature);
  display.setCursor(6, 10);
  display.println(str);

  sprintf(str, PRINT_HUMIDITY, humidity);
  display.setCursor(83, 10);
  display.println(str);
  
  sprintf(str, PRINT_ALTITUDE, altitude);
  display.setCursor(0, 20);
  display.println(str);

  sprintf(str, PRINT_PRESSURE, pressure);
  display.setCursor(60, 20);
  display.println(str);

  display.setCursor(0, 40);
  display.println(getTimeFormattedHHNN());

  display.setCursor(50, 40);
  display.println(WiFi.localIP());

  // display.setCursor(0, 50);
  // display.println("a free line"");

  display.display(); 
}
