#include <Arduino.h>

#include "header.h"

bool sunHasRisen, sunHasSet, dayTime = false;

void setupLEDstrips() {
  pinMode(LED_STRIP_PIN, OUTPUT);
  digitalWrite(LED_STRIP_PIN, LOW);
  Serial.println("LED strips setup");
}

bool timeControlLEDstrips(DateTime now) {
  int timeControl = now.hour() + HOURS_OFFSET;

  if (timeControl == SUNRISE_TIME) {
    sunrise();
  }
  if (timeControl == SUNSET_TIME) {
    sunset();
  }
  if ((timeControl >= SUNRISE_TIME) && (timeControl <= SUNSET_TIME)) {
    return dayTime = true;
  }

  if ((timeControl >= SUNSET_TIME) || (timeControl <= SUNRISE_TIME)) {
    return dayTime = false;
  }
}

void sunrise() {
  sunHasSet = false;
  int sunLevel = 0;

  if (sunHasRisen == false) {
    Serial.println("Sunrise");
    sunHasRisen = true;
    void displaySunriseOnLCD();

    do {
      sunLevel++;
      analogWrite(LED_STRIP_PIN, sunLevel);
      Serial.println(sunLevel);
      delay(SUN_ITERATION_TIME);
      displaySunriseOnLCD();
      if (sunLevel == 255) {
        Serial.println("Sunrise finished");
        sunHasRisen = true;
      }

    } while (sunLevel <= 255);
  }
}

void sunset() {
  sunHasRisen = false;
  int sunLevel = 255;

  if (sunHasSet == false) {
    Serial.println("Sunset");
    sunHasSet = true;

    do {
      sunLevel--;
      analogWrite(LED_STRIP_PIN, sunLevel);
      Serial.println(sunLevel);
      delay(SUN_ITERATION_TIME);
      displaySunsetOnLCD();
      if (sunLevel == 0) {
        Serial.println("Sunset finished");
        sunHasSet = true;
      }

    } while (sunLevel >= 1);
  }
}

void dayNight(bool dayTime) {
  if (dayTime == true) {
    digitalWrite(LED_STRIP_PIN, HIGH);
    Serial.println("It is now day time");
  }
  if (dayTime == false) {
    digitalWrite(LED_STRIP_PIN, LOW);
    Serial.println("It is now night time");
  }
}