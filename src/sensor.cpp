#include <Arduino.h>
#include <HTU21D.h>
#include <Wire.h>

#include "header.h"

HTU21D htu21d(HTU21D_RES_RH8_TEMP12);

void setupHTU21D() {
  htu21d.begin();
  // htu21d.write8();
  Serial.println("HTU21D active");
}

void htu21dSensorHeater(SensorData getSensorData) {
  if (getSensorData.humidity >= 99) {
    htu21d.setHeater(HTU21D_ON);
    Serial.println("Humidity too high, heater on");
  } else {
    htu21d.setHeater(HTU21D_OFF);
  }
}

SensorData getSensorData() {
  htu21d.softReset();
  float temperature = htu21d.readTemperature();
  SensorData getSensorData{
      .temperature = temperature,
      .temperatureAsInt = int(getSensorData.temperature),
      .humidity = htu21d.readHumidity(HTU21D_TRIGGER_HUMD_MEASURE_HOLD),
      .humidityAsInt = int(getSensorData.humidity)};

  htu21dSensorHeater(getSensorData);

  //   Serial.println("Getting sensor data: ");
  //   Serial.println(getSensorData.temperature);
  //   Serial.println(getSensorData.humidity);
  //   Serial.println(getSensorData.humidityAsInt);

  return getSensorData;
}