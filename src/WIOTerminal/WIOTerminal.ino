// Arduino libraries
#include "Arduino.h"

// Local header files
#include "Buttons.hpp"
#include "Buzzer.hpp"
#include "Loudness.hpp"
#include "MqttClient.hpp"
#include "Screen.hpp"
#include "Settings.hpp"
#include "TempHumidity.hpp"
#include "Ultrasonic.hpp"
#include "Util.hpp"

// MQTT publish frequency values
const uint32_t mqttLoopFrequency = 3000;
uint32_t lastTimeMqttLoop;

// Screen update
const uint32_t screenUpdateFrequency = 1000;
uint32_t lastTimeScreenUpdated;

/**
 * Calls each initialization function for each component.
 * Also initializes variables used for the loop().
 *
 * @return void
 */
void setup() {
    // Initialize all components
    screenInit();

    mqttInit();

    tempHumidInit();

    loudnessInit();

    buzzerInit();

    buttonsInit();

    // Initialize loop variables
    lastTimeMqttLoop = 0;
    lastTimeScreenUpdated = 0;

    // Set arbitrary max values since they will be updated by the app
    setMaxPeople(10);
    setMaxTemperature(50);
    setMaxHumidity(50);
    setMaxLoudness(50);
}

/**
 * Main loop of the program.
 * Calls each loop function for each component.
 *
 * @return void
 */
void loop() {
    setCurrentTime(millis());

    // Get data from ultrasonic sensors
    UltrasonicData data;
    data = detectMovement(getPeople());

    // Update locally stored data to sensor readings
    setPeople(data.count);
    setTemperature(measureTemperature());
    setHumidity(measureHumidity());
    setLoudness(loudnessMapped());

    // Calling the loop function for each component

    buzzerLoop();

    buttonsLoop();

    // Updates the screen every "screenUpdateFrequency" milliseconds
    if (getCurrentTime() - lastTimeScreenUpdated > screenUpdateFrequency) {
        updateScreen();
        lastTimeScreenUpdated = getCurrentTime();
    }

    // Does the MQTT loop every "mqttLoopFrequency" milliseconds
    if (getCurrentTime() - lastTimeMqttLoop > mqttLoopFrequency) {
        mqttLoop();
        lastTimeMqttLoop = getCurrentTime();
    }
}
