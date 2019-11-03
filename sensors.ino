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