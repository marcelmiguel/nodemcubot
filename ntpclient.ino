#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Utilities.h>
#include "secrets.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, SECRET_NTPSERVER, NTPZONEFIX);

void initNTPClient() {
    timeClient.begin();
}

void updateNTPClientTime() {
    timeClient.update();
}

String getTimeFormatted() {
    return timeClient.getFormattedTime();
}

String getTimeFormattedHHNN() {
    char str[20];
    sprintf(str, PRINT_HOUR_MINUTES, timeClient.getHours(), timeClient.getMinutes());
    return str;
}
