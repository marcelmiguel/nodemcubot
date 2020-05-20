
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>

WiFiUDP UDP;
IPAddress computer_ip(255,255,255,255); 

void InitWOL() {

}

bool stringToArray(uint8_t* _macAddress, const char* _macString) {
	char macFormat[23 + 1];
	unsigned int tempMACAddress[6];

	if (strlen(_macString) == 12)  // FFFFFFFFFFFF
		sprintf(macFormat, "%%2x%%2x%%2x%%2x%%2x%%2x");
	else if (strlen(_macString) == 14)  // FFFF-FFFF-FFFF
		sprintf(macFormat, "%%2x%%2x%c%%2x%%2x%c%%2x%%2x", _macString[4], _macString[9]);
	else if (strlen(_macString) == 17)  // FF-FF-FF-FF-FF-FF
		sprintf(macFormat, "%%2x%c%%2x%c%%2x%c%%2x%c%%2x%c%%2x", _macString[2], _macString[5], _macString[8], _macString[11], _macString[14]);
	else
		return false;

	int j = sscanf(_macString, (const char*)macFormat, &tempMACAddress[0], &tempMACAddress[1], &tempMACAddress[2], &tempMACAddress[3], &tempMACAddress[4], &tempMACAddress[5]);
	if (j == 6) {
		for (uint8_t i = 0; i < sizeof(tempMACAddress) / sizeof(*tempMACAddress); i++)
			_macAddress[i] = (uint8_t)tempMACAddress[i];

		return true;
	}

	return false;
}

bool WakeOnLan(char *MACAddress) {
    Serial.printf("Wake On LAN %s\n", MACAddress);
    
    uint8_t macAddress[6];

	bool res = stringToArray(macAddress, MACAddress);
	if (!res)
        return false;
    
    WakeOnLan::sendWOL(computer_ip, UDP, macAddress, sizeof macAddress);
    return true;
}

