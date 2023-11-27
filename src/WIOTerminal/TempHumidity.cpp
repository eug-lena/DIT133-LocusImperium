#include "DHT.h"
#include "TempHumidity.hpp"

#define DHTPIN D4

#define DHTTYPE DHT11

DHT tempHumiditySensor(DHTPIN, DHTTYPE);

/**
 * Initialise the temperature and humidity sensor.
 * 
 * @return void
 */
void tempHumidInit() {
    tempHumiditySensor.begin();
}

/**
 * Measure the temperature in celsius.
 * 
 * @return int The temperature as an integer.
 */
int measureTemperature() { 
    return tempHumiditySensor.readTemperature(false);
}

/**
 * Measures the humidity.
 * 
 * @return int Humidity as an integer in a scale from 0 to 100
 */
int measureHumidity() {
    return tempHumiditySensor.readHumidity(); 
}