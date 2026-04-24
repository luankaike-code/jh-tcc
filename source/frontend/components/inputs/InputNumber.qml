import QtQuick

import "./"

Input {
    validator: RegularExpressionValidator {
        regularExpression: /[0-9]+/
    }
}
