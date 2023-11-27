// Local header files
#include "Util.hpp"
#include "Arduino.h"

uint32_t currentTime;

/**
 * To set the current time of the most recent main loop (WIOTerminal.ino loop() method)
 *
 * @note used so the currentTime does not differentiate due to computation time. Otherwise, see millis()
 * @param time what to set the current time to, note: use millis()
 * @return void
 */
void setCurrentTime(uint32_t time) {
    currentTime = time;
}

/**
 * To get the current time of the most recent main loop (WIOTerminal.ino loop() method).
 * 
 * @note used so the current time does not differentiate due to computation time. Otherwise, see millis()
 * @return uint32_t
 */
uint32_t getCurrentTime() {
    return currentTime;
}