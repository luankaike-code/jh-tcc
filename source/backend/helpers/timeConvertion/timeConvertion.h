/*
 * SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef TIMECONVERTION_H
#define TIMECONVERTION_H

class TimeConvertion {
public:
    TimeConvertion();

    static int minutesToMiliseconds(const float& minutes);
    static int milisecondsToMinutes(const float& miliseconds);
};

#endif // TIMECONVERTION_H
