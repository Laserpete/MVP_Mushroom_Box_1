#include <Arduino.h>

#include "header.h"

void setupHumidifier() {
  pinMode(HEATED_WICK_PIN, OUTPUT);
  digitalWrite(HEATED_WICK_PIN, LOW);
  Serial.println("Humidifier setup");
}

bool controlHumidifier(SensorData getSensorData) {
  if (getSensorData.humidity <= HUMIDITY_SETTING) {
    digitalWrite(HEATED_WICK_PIN, HIGH);
    Serial.println("Heated Wick On");
    return true;

  } else {
    digitalWrite(HEATED_WICK_PIN, LOW);
    Serial.println("Heated Wick Off");
    return false;
  }
};
