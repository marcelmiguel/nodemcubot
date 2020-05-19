
#include <WiFiUdp.h>
//#include <WakeOnLan.h>

WiFiUDP UDP;
//WakeOnLan WOL(UDP); // Pass WiFiUDP class

void InitWOL() {
    // Initialization
}

void WakeOnLan(char *MACAddress) {
    Serial.printf("Wake On LAN %s\n", MACAddress);
    //WOL.sendMagicPacket(MACAddress);
    //WOL.sendMagicPacket(MACAddress, 7);
}

