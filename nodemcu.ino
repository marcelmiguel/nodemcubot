#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotInlineKeyboard.h>
#include <Utilities.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>

#include "secrets.h"

// BME280 constants
#define SEALEVELPRESSURE_HPA (1013.25)

// SSD1306 constants
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LED0 3 //D3
#define LED1 1 //D10
#define LED2 2 //
#define LED3 10 //SD3

// Global objects
Adafruit_BME280 bme;
uint ticks=0;
float temperature, humidity, pressure, altitude;
String ssid  = SECRET_SSID;
String pass  = SECRET_PASS;
String token = SECRET_BOT_TOKEN;  
String res = "";
CTBot myBot;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  
  Serial.begin(115200);

  bme.begin(0x76);

  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);
	
  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\nConnected to telegram services");
  else
    Serial.println("\nNo internet access, check wifi");
    
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  printWeatherInfo();

  /*pinMode(LED0, OUTPUT); 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); */
}

void loop() {

  TBMessage msg;

  if (myBot.getNewMessage(msg)) {
    res = "";
    if (msg.text.equals("on")){  
      //TODO on relay
    } else if (msg.text.equals("temp")){    
      temperature = bme.readTemperature();
      res = temperature;
      res += "ºC";
    } else if (msg.text.equals("pressure")){    
      pressure = bme.readPressure() / 100.0F;
      res = pressure;
      res += "hPa";
    } else if (msg.text.equals("humidity")){    
      humidity = bme.readHumidity();
      res = humidity;
      res += "%";
    } else if (msg.text.equals("altitude")){    
      altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
      res = altitude;
      res += "m";
    } else {
      res = msg.text;
    }

    if (res != "") {
      Serial.println(res);
      myBot.sendMessage(msg.sender.id, res);
    }
  }  
	if (ticks % 10) {
    printWeatherInfo();
  }

  ticks ++;
  delay(5000);
}

void printWeatherInfo() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  res = altitude;
  res += "m";
  display.setCursor(0, 10);
  display.println(res);

  humidity = bme.readHumidity();
  res = humidity;
  res += "%";
  display.setCursor(0, 20);
  display.println(res);

  temperature = bme.readTemperature();
  res = temperature;
  res += "ºC";
  display.setCursor(0, 30);
  display.println(res);
  
  pressure = bme.readPressure() / 100.0F;
  res = pressure;
  res += "hPa";
  display.setCursor(0, 40);
  display.println(res);

  display.display(); 
}