// Home Automation project
// Get information of sensors
// etc...

#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotInlineKeyboard.h>
#include <Utilities.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "peripherals.h"
#include "scheduler.h"
#include "display.h"
#include "secrets.h"

// Services
CTBot myBot;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, SECRET_NTPSERVER, NTPZONEFIX);
ESP8266WebServer server(80);

// Peripherals
Adafruit_BME280 bme;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Global objects
uint ticks=0;
float temperature, humidity, pressure, altitude;


void setup() {
  
  Serial.begin(SERIAL_BAUD);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADRRESS)) {
    Serial.println(F("No SSD1306 connected"));
  }
  
  timeClient.begin();

  bme.begin(SENSOR_TEMP_ADDRESS);

  myBot.wifiConnect(SECRET_SSID, SECRET_PASS);

  myBot.setTelegramToken(SECRET_BOT_TOKEN);
	
  bool conn = myBot.testConnection();
  showInitStatus(conn);

  initMDNS();
  timeClient.update();
  getInfoFromSensors();

  printWeatherInfo();

  initWebServerRouter();

}

void loop() {

  if ((ticks % TICKETSSECOND*EVERY_10_SECONDS)==0) { 
    getInfoFromSensors();
    printWeatherInfo();
  }

  if ((ticks % (TICKETSSECOND*EVERY_6_SECONDS))==0) { 
    // This process collapses the system for a few seconds
    handleBotMessages();
  }

  if ((ticks % (TICKETSSECOND*EVERY_1_HOUR))==0) {
    timeClient.update();
    Serial.println("Get time from internet " +timeClient.getFormattedTime());
  }

  server.handleClient();

  ticks ++;
  delay(LOOPSLEEP);

}

void initMDNS() {
   if (!MDNS.begin(SECRET_HOSTNAME)) 
   {             
     Serial.println("Error Initializing mDNS");
   }
   Serial.println("mDNS activated");
}

void initWebServerRouter() {
  server.on("/", handleRoot);
  server.on("/api/v1/weather", handleGetWeatherInfo);
  server.onNotFound(handleNotFound);
  server.begin();
}

void showInitStatus(bool conn) {
  if (conn)
    Serial.println("\nConnected to telegram services");
  else
    Serial.println("\nNo internet access, check wifi");
}

void getInfoFromSensors() {
  temperature = bme.readTemperature();
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
} 

void printWeatherInfo() {
  char str[20];

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
    
  sprintf(str, PRINT_TEMPERATURE, temperature);
  display.setCursor(6, 10);
  display.println(str);

  sprintf(str, PRINT_HUMIDITY, humidity);
  display.setCursor(83, 10);
  display.println(str);
  
  sprintf(str, PRINT_ALTITUDE, altitude);
  display.setCursor(0, 20);
  display.println(str);

  sprintf(str, PRINT_PRESSURE, pressure);
  display.setCursor(60, 20);
  display.println(str);

  display.setCursor(0, 40);
  sprintf(str, PRINT_HOUR_MINUTES, timeClient.getHours(), timeClient.getMinutes());
  display.println(str);

  display.setCursor(50, 40);
  display.println(WiFi.localIP());

  // display.setCursor(0, 50);
  // display.println("a free line"");

  display.display(); 
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

// region WebServer routing
void handleRoot() {
   
  String html = "<!DOCTYPE html><html lang=\"en\"><head> <title>Weather Station</title> <script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script></head><body> <div id=\"chart_div\" style=\"width: 200px; height: 200px;\"></div> <div id=\"chart_div1\" style=\"width: 200px; height: 200px;\"></div> <script> google.charts.load('current', { 'packages': ['gauge'] }); google.charts.setOnLoadCallback(drawChart); function drawChart() { var data = google.visualization.arrayToDataTable([ ['Label', 'Value'], ['Temp º', 24] ]); var data1 = google.visualization.arrayToDataTable([ ['Label', 'Value'], ['Humid. %', 65] ]); var options = { width: 200, height: 200, redFrom: 35, redTo: 50, yellowFrom: 30, yellowTo: 35, minorTicks: 5, min: -40, max: 50 }; var options1 = { width: 200, height: 200, redFrom: 90, redTo: 100, yellowFrom: 75, yellowTo: 90, minorTicks: 5 }; var chart = new google.visualization.Gauge(document.getElementById('chart_div')); var chart1 = new google.visualization.Gauge(document.getElementById('chart_div1')); chart.draw(data, options); chart1.draw(data1, options1); setInterval(function() { fetch('api/v1/weather', { mode: 'no-cors', method: 'GET', headers: { 'Content-Type': 'application/json' }, cache: 'no-cache' }) .then(function(response) { return response.text(); }) .then(function(dataIn) { var obj = JSON.parse(dataIn); data.setValue(0, 1, obj.temperature); chart.draw(data, options); data1.setValue(0, 1, obj.humidity); chart1.draw(data1, options1); console.log('data = ', dataIn); }) .catch(function(err) { console.error(err); }); }, 10000); } </script></body></html>";

  server.send(200, "text/html", html);
}

void handleGetWeatherInfo() {
  String value = "";
  char str[400];

  sprintf(str, "{\"%s\":%4.1f, \"%s\":%2.f, \"%s\":%4.f, \"%s\":%5.f}", 
    "temperature", temperature,
    "humidity", humidity,
    "pressure", pressure,
    "altitude", altitude
    );
  
  server.send(200, "application/json", str);
}

void handleNotFound() {
   server.send(404, "text/plain", "Sorry, Page Not found");
}
// endregion WebServer routing