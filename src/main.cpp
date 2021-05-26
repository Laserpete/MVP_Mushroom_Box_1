/* Controller for MVP Mushroom Box.

  Featrues include ultrasonic mister and LED lights and LCD display

  LEDs controlled by real time clock, ultrasonic mister controlled by feedback
  loop from HTU21D

  Max current draw is 3.3 amps (with Headed wick)

*/

#include <Arduino.h>
#include <Wire.h>

#include "header.h"

#define LOOP_ITERATION_TIME 1
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
  DateTime dateTime = getCurrentTimeFromRTC();
  if (dateTime.unixtime() >= (lastLoop + LOOP_ITERATION_TIME)) {
    lastLoop = dateTime.unixtime();

    serialPrintCurrentTime(dateTime);

    setLEDBrightness(getSunBrightness(dateTime));

    SensorData sensorData = getSensorData();
    humidifierIsOn = controlHumidifier(sensorData);
    whatToDisplayOnLCD(sensorData, dateTime, humidifierIsOn);
  }
}