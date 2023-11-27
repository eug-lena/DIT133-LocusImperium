// Arduino libraries
#include "Arduino.h"

// Local header files
#include "Loudness.hpp"

/**
 * Initialize the loudness input.
 *
 * @return void
 */
void loudnessInit() {
    pinMode(WIO_MIC, INPUT);
}

/**
 * Get the raw value of the loudness sensor.
 * 
 * @return int The raw value of the loudness sensor.
 */
int loudnessRaw() {
  int val = analogRead(WIO_MIC);
  return val;
}

/**
 * Get the loudness level mapped from 0 to 100.
 * 
 * @return int The loudness level.
 */
int loudnessMapped() {
    int val = loudnessRaw();
    int level = map(val, 0, 1023, 0, 100);
    return level;
}
