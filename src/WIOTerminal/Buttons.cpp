// Arduino libraries
#include "Arduino.h"

// Local header files
#include "Buttons.hpp"
#include "Settings.hpp"

/**
 * Initialize the physical buttons on the Wio Terminal.
 *
 * @return void
 */
void buttonsInit() {
    pinMode(WIO_KEY_A, INPUT);  // increase button
    pinMode(WIO_KEY_B, INPUT);  // decrease button
}

/**
 * Check if either of the used buttons are pressed and call the appropriate function.
 *
 * @return void
 */
void buttonsLoop() {
    // Increase people count
    if (digitalRead(WIO_KEY_A) == LOW) {
        setPeople(getPeople() + 1);
    }

    // Decrease people count
    if (digitalRead(WIO_KEY_B) == LOW) {
        // Check if people is greater than 0 to prevent negative people count
        if (getPeople() > 0) {
            setPeople(getPeople() - 1);
        }
    }
}