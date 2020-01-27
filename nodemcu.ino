// Home Automation project
// Get information of sensors
// etc...

#include "peripherals.h"
#include "scheduler.h"
#include "display.h"
#include "secrets.h"
#include "globals.h"

// Global objects
uint ticks=0;

void setup() {

  Serial.begin(SERIAL_BAUD);

  initConfig();

  initDisplay();
  initNTPClient();
  initSensors();
  initTelegramBot();
  initMDNS();

  updateNTPClientTime();
  getInfoFromSensors();
  getMoistureMesures();
  printWeatherInfo();

  initWebServerRouter();

  initConfig();

}

void loop() {

  if ((ticks % EVERY_10_SECONDS)==0) {
    getInfoFromSensors();
    getMoistureMesures();
    printWeatherInfo();
  }

  if ((ticks % EVERY_6_SECONDS)==0) {
    handleBotMessages();
  }

  if ((ticks % EVERY_1_HOUR)==0) {
    updateNTPClientTime();
    Serial.println("Get time from internet " +getTimeFormatted());
  }

  webServerDoStuff();

  ticks ++;
  delay(LOOPSLEEP);

}
