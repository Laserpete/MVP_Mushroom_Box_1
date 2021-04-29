#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>

#include "header.h"

RTC_DS3231 rtc;

void setupClock() {
  rtc.begin();
  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.disable32K();
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void checkTimeAtInterval();

DateTime getCurrentTimeFromRTC() {
  DateTime now = rtc.now();
  Serial.print("Current time is ");
  Serial.print(now.hour() + HOURS_OFFSET);
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());
  return now;
}