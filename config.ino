#include <ESP8266NetBIOS.h>
#include <Utilities.h>
#include <EEPROM.h>
#include "globals.h"

void initConfig() {
  Serial.printf("\n\nSdk version: %s\n", ESP.getSdkVersion());
  Serial.printf("Core Version: %s\n", ESP.getCoreVersion().c_str());
  Serial.printf("Boot Version: %u\n", ESP.getBootVersion());
  Serial.printf("Boot Mode: %u\n", ESP.getBootMode());
  Serial.printf("CPU Frequency: %u MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Reset reason: %s\n", ESP.getResetReason().c_str());
  Serial.printf("Chip ID: %u\n\n", ESP.getFlashChipId());
  
  // TODO read confguration from Serial
  // TODO wait for two seconds to press F11 and enter 
  // TODO   configuration mode in case already configured
  /*loadCredentials();

  if (!validCredentials()) {
    Serial.println("---------------------------");
    Serial.println("------ INITIAL CONFIG -----");
    Serial.println("---------------------------\n");

    Serial.flush();

    ssid = getStringSerial("\nInsert wifi ssid: ");
    password = getStringSerial("\nInsert wifi password: ");
  }*/
  
}

String getStringSerial(String ask) {
    String res = "";

    Serial.println(ask);

    while (true) {
        if (Serial.available()) {
            char ch = Serial.read();
            if (ch == 13) { // return
                break;
            } else if (ch == 27) { // ESC
                res = "";
                break;
            }
            res = res + ch;
        }
        delay(2); 
    }

    return res;
}

void loadCredentials() {
  EEPROM.begin(512);
  EEPROM.get(0, ssid);
  EEPROM.get(0+sizeof(ssid), password);
  char ok[2+1];
  EEPROM.get(0+sizeof(ssid)+sizeof(password), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    ssid[0] = 0;
    password[0] = 0;
  }
  Serial.println("Recovered credentials:");
  Serial.println(ssid);
  Serial.println((password.length())>0?"********":"<no password>");
}

/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0+sizeof(ssid), password);
  char ok[2+1] = "OK";
  EEPROM.put(0+sizeof(ssid)+sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
}

bool validCredentials() {
    return ((ssid.length()>0) && (password.length()>0));
}