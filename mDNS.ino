#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "secrets.h"

void initMDNS() {
   if (!MDNS.begin(SECRET_HOSTNAME)) 
   {             
     Serial.println("Error Initializing mDNS");
   }
   Serial.println("mDNS activated");
}