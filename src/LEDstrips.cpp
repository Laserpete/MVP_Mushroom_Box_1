#include <Arduino.h>

#include "header.h"

bool sunHasRisen, sunHasSet = false;

void setupLEDstrips() {
  pinMode(LED_STRIP_PIN, OUTPUT);
  digitalWrite(LED_STRIP_PIN, LOW);
  Serial.println("LED strips setup");
}

void timeControlLEDstrips(DateTime now) {
  int timeControl = now.minute() + HOURS_OFFSET;

  if (timeControl == SUNRISE_TIME) {
    sunrise();
  }
  if (timeControl == SUNSET_TIME) {
    sunset();
  }
  if ((timeControl >= SUNRISE_TIME) && (timeControl <= SUNSET_TIME)) {
    day();
  }

  if ((timeControl >= SUNSET_TIME) || (timeControl <= SUNRISE_TIME)) {
    night();
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

void day() {
  digitalWrite(LED_STRIP_PIN, HIGH);
  Serial.println("LED Pin digital write high");
  Serial.println("It is now day time");
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
    night();
  }
}

void night() {
  digitalWrite(LED_STRIP_PIN, LOW);
  Serial.println("LED Pin digital write low");
  Serial.println("It is now night time");
}