import QtQuick

import QtQuick.Controls
import "./"

Label {
    required property list<MagnitudeObj> magnitudes
    property list<MagnitudeObj> magnitudesOrganized

    property real value: 0

    function getTextContent() {
        let magnitudeSymbol = ""
        let magnitudeValue = 0
        let caughtMagnitudeData = false

        for(let magnitude of magnitudesOrganized) {
            if(value < magnitude.value) {
                caughtMagnitudeData = true
                break
            }

            magnitudeSymbol = magnitude.symbol
            magnitudeValue = magnitude.value
        }

        if(!caughtMagnitudeData) {
            magnitudeSymbol = magnitudesOrganized[0].symbol
            magnitudeValue = magnitudesOrganized[0].value
        }

        let realValue = value / magnitudeValue

        if(realValue && realValue%1 !== 0)
            realValue = realValue.toFixed(1)
        else if(!realValue)
            realValue = ""
        console.log(realValue, "|", magnitudeSymbol, "|", qsTr("%1 %2").arg(realValue).arg(magnitudeSymbol))
        return qsTr("%1 %2").arg(realValue).arg(magnitudeSymbol)
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
