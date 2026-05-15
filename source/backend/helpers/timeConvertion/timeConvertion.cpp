#include "timeConvertion.h"

TimeConvertion::TimeConvertion() {}

int TimeConvertion::minutesToMiliseconds(const float& minutes) {
    return minutes*60*1000;
}

int TimeConvertion::milisecondsToMinutes(const float& miliseconds) {
    return (miliseconds/1000)/60;
}