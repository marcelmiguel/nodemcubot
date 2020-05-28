#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotInlineKeyboard.h>
#include "globals.h"

CTBot myBot;
TBMessage msg;
char str[60];

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
  if (myBot.getNewMessage(msg)) {
    
    if (!secureAccess(msg.sender.id)) {
      myBot.sendMessage(msg.sender.id, "No rights to use this bot");
      return;
    }

    if (msg.text.equals("/motionon")){
      motionOn();
      sprintf(str, "Motion on");
      myBot.sendMessage(msg.sender.id, str);
    } else if (msg.text.equals("/motionoff")){
      motionOff();
      sprintf(str, "Motion off");
      myBot.sendMessage(msg.sender.id, str);
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
    } else if (msg.text.equals("/tempovo")){    
      sprintf(str, PRINT_TEMPERATURE, temperature);
      myBot.sendMessage(msg.sender.id, str);
    } else if (msg.text.equals("/wolpc1")){    
      sprintf(str, "Starting PC1");
      WakeOnLan(WAKONLAN_MAC_PC1);
      myBot.sendMessage(msg.sender.id, str);
    } else if (msg.text.equals("/wolpc2")){    
      WakeOnLan(WAKONLAN_MAC_PC2);
      sprintf(str, "Starting PC2");
      myBot.sendMessage(msg.sender.id, str);
    }
    // weight
    // position
  }  

}

bool secureAccess(uint sender_id) {
  if (sender_id == BOT_USERID1) {
    return true;
  } else if (sender_id == BOT_USERID2) {
    return true;
  } else if (sender_id == BOT_USERID3) {
    return true;
  }
  
  return false;
}