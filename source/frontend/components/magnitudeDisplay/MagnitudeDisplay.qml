import QtQuick

import QtQuick.Controls
import "./"

Label {
    required property list<MagnitudeObj> magnitudes
    property list<MagnitudeObj> magnitudesOrganized

    property real value: 0

    function getTextContent() {
        let magnitude_symbol = ""
        let magnitude_value = 0

        for(let magnitude of magnitudesOrganized) {
            if(value < magnitude.value)
                break

            magnitude_symbol = magnitude.symbol
            magnitude_value = magnitude.value
        }

        let real_value = value / magnitude_value

        if(real_value && real_value%1 !== 0)
            real_value = real_value.toFixed(1)
        else if(!real_value)
            real_value = ""

        return qsTr("%1 %2").arg(real_value).arg(magnitude_symbol)
    }

    onValueChanged: {
        text = getTextContent()
    }

    onMagnitudesChanged: {
        magnitudesOrganized = magnitudes
        magnitudesOrganized.sort((a, b) => {
            if(a.value > b.value)
                return 1
            else if(a.value < b.value)
                return -1
            else
                return 0
        })
    }

    text: getTextContent()
}
