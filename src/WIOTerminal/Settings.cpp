// Local header files
#include "Settings.hpp"

int maxPeople;
int maxTemperature;
int maxHumidity;
int maxLoudness;
int people;
int temperature;
int humidity;
int loudness;

/**
 * Get the value for the temperature in the room.
 *
 * @return int, The temperature in the room.
 */
int getTemperature() {
    return temperature;
}

/**
 * Set the value for the temperature in the room.
 *
 * @param newTemperature The temperature in the room.
 * @return void
 */
void setTemperature(int newTemperature) {
    temperature = newTemperature;
}

/**
 * Get the value for the humidity in the room.
 *
 * @return int, The humidity in the room.
 */

int getHumidity() {
    return humidity;
}

/**
 * Set the value for the humidity in the room.
 *
 * @param newHumidity The humidity in the room.
 * @return void
 */
void setHumidity(int newHumidity) {
    humidity = newHumidity;
}

/**
 * Get the value for the loudness level in the room.
 *
 * @return int, The loudness level in the room.
 */

int getLoudness() {
    return loudness;
}

/**
 * Set the value for the loudness level in the room.
 *
 * @param newLoudness The loudness level in the room.
 * @return void
 */
void setLoudness(int newLoudness) {
    loudness = newLoudness;
}

/**
 * Get the value for the number of people in the room.
 *
 * @return int, The number of people in the room.
 */
int getPeople() {
    return people;
}

/**
 * Get the value for the number of people in the room.
 *
 * @param newPeople The number of people in the room.
 * @return int, The number of people in the room.
 */
void setPeople(int newPeople) {
    people = newPeople;
}

/**
 * Get the value for the maximum number of people allowed in the room.
 *
 * @return int, The maximum number of people allowed in the room.
 */
int getMaxPeople() {
    return maxPeople;
}

/**
 * Set the value for the maximum number of people allowed in the room.
 *
 * @param newMaxPeople The maximum number of people allowed in the room.
 * @return void
 */
void setMaxPeople(int newMaxPeople) {
    maxPeople = newMaxPeople;
}

/**
 * Set the value for the maximum temperature allowed in the room.
 *
 * @return int, The maximum temperature allowed in the room.
 */
int getMaxTemperature() {
    return maxTemperature;
}

/**
 * Set the value for the maximum temperature allowed in the room.
 *
 * @param newMaxTemperature The maximum temperature allowed in the room.
 * @return void
 */
void setMaxTemperature(int newMaxTemperature) {
    maxTemperature = newMaxTemperature;
}

/**
 * Set the value for the maximum humidity value allowed in the room.
 *
 * @return int, The maximum humidity value allowed in the room.
 */
int getMaxHumidity() {
    return maxHumidity;
}

/**
 * Set the value for the maximum humidity value allowed in the room.
 *
 * @param newMaxHumidity The maximum humidity value allowed in the room.
 * @return void
 */
void setMaxHumidity(int newMaxHumidity) {
    maxHumidity = newMaxHumidity;
}

/**
 * Set the value for the maximum loudness level allowed in the room.
 *
 * @return int, The maximum loudness level allowed in the room.
 */
int getMaxLoudness() {
    return maxLoudness;
}

/**
 * Set the value for the maximum loudness level allowed in the room.
 *
 * @param newMaxLoudness The maximum loudness level allowed in the room.
 * @return void
 */
void setMaxLoudness(int newMaxLoudness) {
    maxLoudness = newMaxLoudness;
}