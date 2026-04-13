import QtQuick 2.15

import "./"

Input {
    validator: RegularExpressionValidator {
        regularExpression: /[0-9]+/
    }
}
