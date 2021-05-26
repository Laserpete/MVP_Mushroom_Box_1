#include <RTClib.h>

#define LED_STRIP_PIN 6
#define HUMIDIFIER_PIN 5

#define HUMIDITY_SETTING 90

#define HOURS_OFFSET 1

#define DISPLAY_SWITCH_TIME 10

#define MAXIMUM_LIGHT_LEVEL_PWM 255
#define HOURS_OF_LIGHT 12
#define DAYTIME_OFFSET 0

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
void displayHumidifierStatusOnLCD(SensorData, bool);

void setupHumidifier();
bool controlHumidifier(SensorData);

void setupLEDstrips();
int determineSunriseTime();
int determineSunsetTime();
int getSunBrightness(DateTime);
void setLEDBrightness(int);

bool timeControlLEDstrips(DateTime);
void sunrise();
void sunset();
void dayNight(bool);

void setupClock();
DateTime getCurrentTimeFromRTC();
void serialPrintCurrentTime(DateTime now);