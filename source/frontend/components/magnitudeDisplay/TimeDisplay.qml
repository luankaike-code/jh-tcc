// SPDX-FileCopyrightText: 2026 luankaike-code <https://github.com/luankaike-code>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import "./"

MagnitudeDisplay {
    magnitudes: [
        MagnitudeObj {
            value: 1
            symbol: qsTr("ms")
        },
        MagnitudeObj {
            value: 1000
            symbol: qsTr("seg")
        },
        MagnitudeObj {
            value: 1000*60
            symbol: qsTr("min")
        },
        MagnitudeObj {
            value: 1000*60*60
            symbol: qsTr("horas")
        },
        MagnitudeObj {
            value: 1000*60*60*24
            symbol: qsTr("dias")
        }
    ]
}