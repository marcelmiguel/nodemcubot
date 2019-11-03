#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotInlineKeyboard.h>
#include "globals.h"

CTBot myBot;

bool initTelegramBot() {
    myBot.wifiConnect(SECRET_SSID, SECRET_PASS);

    myBot.setTelegramToken(SECRET_BOT_TOKEN);
	
    bool connected = myBot.testConnection();

    if (connected)
      Serial.println("\nConnected to telegram services");
    else
      Serial.println("\nNo internet access, check wifi");
      
    return connected;
}

void handleBotMessages() {
  
  TBMessage msg;
  
  if (myBot.getNewMessage(msg)) {
    char str[20];

    if (msg.text.equals("/on1")){  
      //TODO switch relay
    } else if (msg.text.equals("/temp")){    
      sprintf(str, PRINT_TEMPERATURE, temperature);
      myBot.sendMessage(msg.sender.id, str);
    } else if (msg.text.equals("/pressure")){    
      sprintf(str, PRINT_PRESSURE, pressure);
      myBot.sendMessage(msg.sender.id, str);
    } else if (msg.text.equals("/humidity")){    
      sprintf(str, PRINT_HUMIDITY, humidity);
      myBot.sendMessage(msg.sender.id, str);
    } else if (msg.text.equals("/altitude")){    
      sprintf(str, PRINT_ALTITUDE, altitude);
      myBot.sendMessage(msg.sender.id, str);
    }
  }  

}