#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotInlineKeyboard.h>
#include <Utilities.h>
#include "secrets.h"

#define LED0 3 //D3
#define LED1 1 //D10
#define LED2 2 //
#define LED3 10 //SD3
 
String ssid  = SECRET_SSID;
String pass  = SECRET_PASS;
String token = SECRET_BOT_TOKEN;  

String temp = "temperature 35.3 º";

CTBot myBot;

void setup() {
  
  Serial.begin(115200);

  myBot.wifiConnect(ssid, pass);

	// set the telegram bot token
	myBot.setTelegramToken(token);
	
	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");
    
  /*pinMode(LED0, OUTPUT); 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); */
}

void loop() {

  TBMessage msg;

	if (myBot.getNewMessage(msg))
	  if (msg.text.equals("on")){  

    }else if (msg.text.equals("temp")){    
      myBot.sendMessage(msg.sender.id, temp);
      Serial.println(temp);
    } else {
      myBot.sendMessage(msg.sender.id, msg.text);
    }
	// wait 500 milliseconds
	delay(500);
}
