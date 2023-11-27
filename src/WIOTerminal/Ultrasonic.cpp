#include "Ultrasonic.hpp"

#include "Settings.hpp"
#include "Buzzer.hpp"
#include <Ultrasonic.h>

// Initializing the ultrasonic sensors on pins D0 and D2
Ultrasonic ultrasonic1(0);
Ultrasonic ultrasonic2(2);

int time1 = 0;
int time2 = 0;

int threshHold = 200;

/**
 * Detect the movement of a person.
 *
 * @param count Number of people counted so far.
 * @return UltrasonicData The new number of people counted.
 */
UltrasonicData detectMovement(int count) {
    UltrasonicData data;

    long rangeInCentimeters1;
    long rangeInCentimeters2;

    // measure the distance
    rangeInCentimeters1 = ultrasonic1.MeasureInCentimeters();  // two measurements should keep an interval
    delay(50);
    rangeInCentimeters2 = ultrasonic2.MeasureInCentimeters();

    data.distance1 = rangeInCentimeters1;
    data.distance2 = rangeInCentimeters2;

    // checking if the person is passing
    if (rangeInCentimeters1 < threshHold) {
        time1 = millis();
    }

    if (rangeInCentimeters2 < threshHold) {
        time2 = millis();
    }

    //*****************************
    // ! code inspired by https://www.sensingthecity.com/detecting-movement-direction-with-two-ultrasonic-distance-sensors/
    //*****************************
    if (time1 > 0 && time2 > 0) {  // if both sensors have nonzero timestamps
                                   // check if the difference between the timestamps is less than 1300ms
        if (abs(time1 - time2) < 1500) {
            if (time1 < time2) {  // if left sensor triggered first
                count++;          // direction is left to right
                if (getPeople() > (getMaxPeople() - 1)) { // -1 since getPeople is delayed by 1
                    forceBuzzerAlert();
                }
            } else if (time2 < time1) {  // if right sensor triggered first
                count--;                 // direction is right to left
            }
        } else {
            // zero the timestamps if both are non zero
            if (time1 != 0 && time2 != 0) {
                time1 = 0;
                time2 = 0;
            }
        }

        // after printing direction, reset both timestamps to 0
        time1 = 0;
        time2 = 0;
    }

    if (count < 0) {  // prevent the count to go below 0
        count = 0;
    }

    data.count = count;

    return data;
}