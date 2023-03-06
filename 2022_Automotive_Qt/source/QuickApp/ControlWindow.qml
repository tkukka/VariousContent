import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.settings

Window {
    id: root
    title: qsTr("Controls")
    visible: true
    width: 700
    height: 110
    flags: Qt.Tool | Qt.rootStaysOnTop

    property bool turnLeft: false
    property bool turnRight: false
    property bool hazardOn: false
    property bool powered: false
    property bool parkingBrakeOn: false
    property alias throttle: throttle.throttleValue
    signal recharged()

    Column {
        RowLayout {
            spacing: 40
            CheckBox {
                Layout.leftMargin: 10
                enabled: !root.turnRight && !root.hazardOn
                text: qsTr("Turn Left")
                font.pixelSize: 16
                onToggled: root.turnLeft = !root.turnLeft
            }
            CheckBox {
                enabled: !root.turnLeft && !root.hazardOn
                text: qsTr("Turn Right")
                font.pixelSize: 16
                onToggled: root.turnRight = !root.turnRight
            }
            CheckBox {
                enabled: !root.turnLeft && !root.turnRight
                text: qsTr("Hazard Lights")
                font.pixelSize: 16
                onToggled: root.hazardOn = !root.hazardOn
            }
            CheckBox {
                id: powerCheckBox
                text: qsTr("Power on")
                font.pixelSize: 16
                onToggled: root.powered = !root.powered
            }
            CheckBox {
                id: parkingBrakeCheckBox
                text: qsTr("Parking brake on")
                font.pixelSize: 16
                onToggled: root.parkingBrakeOn = !root.parkingBrakeOn
            }


        } //rowlayout 1

        RowLayout {
            spacing: 40

            Button {
                id: rechargeButton
                Layout.topMargin: 10
                Layout.leftMargin: 10
                text: qsTr("Recharge")
                font.pixelSize: 16
                onClicked: {
                    recharged()
                }
            }

            Throttle {
                id: throttle
                topPadding: 10
            }

        } //rowlayout 2
    }

    Settings {
        fileName: "parking_brake.ini"
        property alias parked: root.parkingBrakeOn
        property alias parkingCheckBox: parkingBrakeCheckBox.checked
    }

} // window
