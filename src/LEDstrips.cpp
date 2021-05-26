#include <Arduino.h>
#include <RTClib.h>

#include "header.h"

unsigned int lastLEDStripChange = 0;

void setupLEDstrips() {
  pinMode(LED_STRIP_PIN, OUTPUT);
  digitalWrite(LED_STRIP_PIN, LOW);
  Serial.println("LED strips setup");
}

int determineSunriseTime() {
  return (12 - (HOURS_OF_LIGHT / 2) + DAYTIME_OFFSET);
}

int determineSunsetTime() {
  return (12 + (HOURS_OF_LIGHT / 2) + DAYTIME_OFFSET);
}

int getSunBrightness(DateTime now) {
  static int currentBrightness;
  // If it is time for sunrise, iterate the light level upwards
  if (now.hour() == determineSunriseTime()) {
    if (currentBrightness < MAXIMUM_LIGHT_LEVEL_PWM) {
      currentBrightness++;
      Serial.print("Sunrise ");
      Serial.println(currentBrightness);
      return currentBrightness;
    } else {
      return MAXIMUM_LIGHT_LEVEL_PWM;
    }
  } else if (now.hour() == determineSunsetTime()) {
    if (currentBrightness > 0) {
      currentBrightness--;
      Serial.print("Sunset ");
      Serial.println(currentBrightness);
      return currentBrightness;
    } else {
      return 0;
    }
  } else if ((now.hour() < determineSunriseTime()) or
             (now.minute() > determineSunsetTime())) {
    Serial.println("Night Time");
    currentBrightness = 0;
    return currentBrightness;
  } else if ((now.hour() > determineSunriseTime()) and
             (now.minute() < determineSunsetTime())) {
    Serial.println("Day Time");
    currentBrightness = MAXIMUM_LIGHT_LEVEL_PWM;
    return currentBrightness;
  }
}

void setLEDBrightness(int desiredBrightness) {
  analogWrite(LED_STRIP_PIN, desiredBrightness);
}