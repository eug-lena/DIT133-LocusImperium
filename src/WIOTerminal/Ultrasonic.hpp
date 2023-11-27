#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

#include "Settings.hpp"
#include "Buzzer.hpp"
#include <Ultrasonic.h>

struct UltrasonicData {
    int count;
    int distance1;
    int distance2;
};

UltrasonicData detectMovement(int count);

#endif