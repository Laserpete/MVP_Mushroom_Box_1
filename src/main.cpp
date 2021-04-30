/* Controller for MVP Mushroom Box.

  Featrues include heated wick humidifier and LED lights and LCD display

  LEDs controlled by real time clock, humidifier controlled by feedback loop
  from HTU21D

  Max current draw is 3.3 amps

*/

#include <Arduino.h>
#include <Wire.h>

#include "header.h"

#define LOOP_TIME 1000
unsigned long lastLoop = 0;
bool humidifierIsOn;

void setup() {
  Serial.begin(9600);
  setupClock();
  setupHumidifier();
  setupLEDstrips();
  setupLCD();
  setupHTU21D();
}

void loop() {
  if (millis() >= (lastLoop + LOOP_TIME)) {
    lastLoop = millis();
    SensorData sensorData = getSensorData();
    DateTime dateTime = getCurrentTimeFromRTC();

    timeControlLEDstrips(dateTime);
    humidifierIsOn = controlHumidifier(sensorData);
    whatToDisplayOnLCD(sensorData, dateTime, humidifierIsOn);
  }
}