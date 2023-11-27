// Local header files
#include "Buzzer.hpp"
#include "Util.hpp"

// General
const u_int16_t BUZZER_PIN = 6;
bool isTurnedOn;
const uint32_t alertLength = 500;
uint32_t shouldTurnOffAt;
uint32_t alertFrequency = 10000;

/**
 * Initialize the buzzer.
 *
 * @return void
 */
void buzzerInit() {
    shouldTurnOffAt = 0;
    // pinMode(WIO_BUZZER, OUTPUT); // To use inbuilt buzzer
    pinMode(BUZZER_PIN, OUTPUT); // Grove buzzer
    isTurnedOn = false;
}

/**
 * Checks if the buzzer should turn off.
 *
 * @return void
 */
void buzzerLoop() {
    if (isTurnedOn && getCurrentTime() - shouldTurnOffAt > alertLength) {
        turnOffBuzzer();
    }
}

/**
 * Turn on the buzzer if it has not been played to recently.
 *
 * @return void
 */
void buzzerAlert() {
    if (getCurrentTime() - shouldTurnOffAt > alertFrequency) {
        shouldTurnOffAt = getCurrentTime() + alertLength;
        turnOnBuzzer();
    }
}

/**
 * Turn on the buzzer alert even if it was played recently.
 *
 * @return void
 */
void forceBuzzerAlert() {
    shouldTurnOffAt = getCurrentTime() + alertLength;
    turnOnBuzzer();
}

/**
 * Turn on buzzer and sets isTurnedOn to true.
 *
 * @return void
 */
void turnOnBuzzer() {
    // digitalWrite(WIO_BUZZER, 100); // To use inbuilt buzzer
    digitalWrite(BUZZER_PIN, HIGH); // Grove buzzer
    isTurnedOn = true;
}

/**
 * Turn off buzzer and sets isTurnedOn to false.
 *
 * @return void
 */
void turnOffBuzzer() {
    // digitalWrite(WIO_BUZZER, 0); // To use inbuilt buzzer
    digitalWrite(BUZZER_PIN, LOW); // Grove buzzer
    isTurnedOn = false;
}
