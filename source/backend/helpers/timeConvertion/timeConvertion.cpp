// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "timeConvertion.h"

TimeConvertion::TimeConvertion() {}

int TimeConvertion::minutesToMiliseconds(const float& minutes) {
    return minutes*60*1000;
}

int TimeConvertion::milisecondsToMinutes(const float& miliseconds) {
    return (miliseconds/1000)/60;
}