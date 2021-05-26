#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "header.h"

unsigned long lastDisplaySwitch = 0;
short displayIterator = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupLCD() {
  lcd.init();  // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  byte a[8] = {B01000, B10100, B01000, B00000, B00000, B00000, B00000, B00000};
  lcd.createChar(1, a);
  lcd.print("Hallo Pilze");
  Serial.println("LCD Aktiv");
}

void whatToDisplayOnLCD(SensorData sensorData, DateTime now,
                        bool humidifierIsOn) {
  if (now.unixtime() >= lastDisplaySwitch + DISPLAY_SWITCH_TIME) {
    // Serial.println("Display switch");
    lastDisplaySwitch = now.unixtime();
    if (displayIterator == 3) {
      displayIterator = 0;
    }
    switch (displayIterator) {
      case 0:
        displaySensorDataOnLCD(sensorData);
        break;
      case 1:
        displayTimeOnLCD(now);
        break;
      case 2:
        displayHumidifierStatusOnLCD(sensorData, humidifierIsOn);
        break;
    }
    ++displayIterator;
  }
}

void displaySensorDataOnLCD(SensorData sensorData) {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp   : ");
  lcd.print(sensorData.temperature);
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Feucht : ");
  lcd.print(sensorData.humidityAsInt);
  lcd.print("% rF");
}

void displayTimeOnLCD(DateTime now) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zeit : ");
  if (now.hour() < 10) {
    lcd.print("0");
  }
  lcd.print(now.hour() + HOURS_OFFSET);
  lcd.print(":");
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute());
  /*
  lcd.print(":");
  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second());
  */
}

void displaySunriseOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sonnenaufgang");
}
void displaySunsetOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sonnenuntergang");
}

void displayHumidifierStatusOnLCD(SensorData sensorData, bool humidifierIsOn) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Feucht : ");
  lcd.print(sensorData.humidityAsInt);
  lcd.print(" % rF");
  lcd.setCursor(0, 1);
  if (humidifierIsOn) {
    lcd.print("Vernebler ein");
  } else {
    lcd.print("Vernebler aus");
  }
}