#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "secrets.h"

Adafruit_BME280 bme;

void initSensors() {
    bme.begin(SENSOR_TEMP_ADDRESS);
}

void getInfoFromSensors() {
  temperature = bme.readTemperature();
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
}

void getMoistureMesures() {
  int output_value;
  output_value = analogRead(MOISTURE_PIN);
  // Serial.print("Moisture : ");
  // Serial.print(output_value);
  // Serial.print("\n");
  moisture_level = map(output_value,561,330,0,100);
}
