import QtQuick

Item {
    id: root
    width: row.width
    height: row.height
    property bool leftTurnSignalOn: false
    property bool rightTurnSignalOn: false

    Row {
        id: row
        spacing: 300
        Item {
            id: turnLeftItem
            width: 60
            height: 60
            property bool offIconVisible: !root.leftTurnSignalOn ? true : !turnTimer.blinkOn
            Image {
                id: turnLeftOffImg
                source: turnLeftItem.offIconVisible ? "images/turnleft_off.png" : "images/turnleft_on.png"
            }

        }
        Item {
            id: turnRightItem
            width: 60
            height: 60
            property bool offIconVisible: !root.rightTurnSignalOn ? true : !turnTimer.blinkOn
            Image {
                id: turnRightOffImg
                source: turnRightItem.offIconVisible ? "images/turnright_off.png" : "images/turnright_on.png"
            }
        }
    }// row

    Timer {
        id: turnTimer
        property bool blinkOn: false
        running: root.leftTurnSignalOn || root.rightTurnSignalOn
        repeat: true
        interval: 500
        onTriggered: {
            blinkOn = !blinkOn
        }
    }
}
