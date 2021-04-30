#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "header.h"

unsigned long lastDisplayToggle = 0;
bool displayToggle = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupLCD() {
  lcd.init();  // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello Mushrooms");
  Serial.println("LCD Active");
}

void whatToDisplayOnLCD(SensorData sensorData, DateTime time,
                        bool humidifierIsOn) {
  if (humidifierIsOn == true) {
    displayHumidifierStatusOnLCD(sensorData);
  } else {
    if (millis() > (lastDisplayToggle + DISPLAY_TOGGLE_TIME)) {
      lastDisplayToggle = millis();
      displayToggle = !displayToggle;
    }
    if (displayToggle == true) {
      displaySensorDataOnLCD(sensorData);
    } else {
      displayTimeOnLCD(time);
    }
  }
}

void displaySensorDataOnLCD(SensorData sensorData) {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp  :");
  lcd.print(sensorData.temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Feucht: ");
  lcd.print(sensorData.humidityAsInt);
  lcd.print(" % RH");
}

void displayTimeOnLCD(DateTime time) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time : ");
  lcd.print(time.hour() + HOURS_OFFSET);
  lcd.print(":");
  lcd.print(time.minute());
  lcd.print(":");
  lcd.print(time.second());
}

void displaySunriseOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Sunrise");
}
void displaySunsetOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Sunset");
}

void displayHumidifierStatusOnLCD(SensorData sensorData) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Feucht: ");
  lcd.print(sensorData.humidityAsInt);
  lcd.print(" % RH");
  lcd.setCursor(0, 1);
  lcd.print("Humidifier is On");
}