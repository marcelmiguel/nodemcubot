#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotInlineKeyboard.h>
#include <Utilities.h>
#include "secrets.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

float temperature, humidity, pressure, altitude;

#define LED0 3 //D3
#define LED1 1 //D10
#define LED2 2 //
#define LED3 10 //SD3
 
String ssid  = SECRET_SSID;
String pass  = SECRET_PASS;
String token = SECRET_BOT_TOKEN;  

String res = "";

CTBot myBot;

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
	
  delay(1000);
}
