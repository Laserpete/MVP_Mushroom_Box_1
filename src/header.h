#include <RTClib.h>

#define LED_STRIP_PIN 6
#define HEATED_WICK_PIN 5

#define HUMIDITY_SETTING 90

#define CHECK_TIME_INTERVAL 1

#define HOURS_OFFSET 1

#define SUN_ITERATION_TIME 50

#define DISPLAY_TOGGLE_TIME 10000

#define SUNRISE_TIME 8
#define SUNSET_TIME 20

typedef struct _SensorData {
  float temperature;
  int temperatureAsInt;
  float humidity;
  int humidityAsInt;
} SensorData;

void setupPins();

void setupHTU21D();
void htu21dSensorHeater(SensorData);
SensorData getSensorData();

void setupLCD();
void whatToDisplayOnLCD(SensorData, DateTime, bool);
void displaySensorDataOnLCD(SensorData);
void displayTimeOnLCD(DateTime);
void displayStatusOnLCD();
void displaySunriseOnLCD();
void displaySunsetOnLCD();
void displayHumidifierStatusOnLCD(SensorData);

void setupHumidifier();
bool controlHumidifier(SensorData);

void setupLEDstrips();
void timeControlLEDstrips(DateTime);
void sunrise();
void day();
void sunset();
void night();

void setupClock();
void checkTimeAtInterval();
DateTime getCurrentTimeFromRTC();