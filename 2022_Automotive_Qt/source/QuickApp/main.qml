import QtQuick
import QuickApp

Window {
    id: window
    width: 780
    height: 640
    visible: true
    title: "Automotive Code Now Project 2022"

    // second window
    ControlWindow {
        id: controlWindow
        onRecharged: {
            myCar.charge = myCar.maxCharge
        }
    }


    // ---------------------------------------     main UI      -------------------------------
    Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white"}
            GradientStop { position: 0.1; color: "gray"}
            GradientStop { position: 1.0; color: "black"}
        }
        anchors.fill: window.contentItem
    }

    SignalPane {
        id: signalPane
        anchors.horizontalCenter: speedGauge.horizontalCenter

        leftTurnSignalOn: controlWindow.turnLeft || controlWindow.hazardOn
        rightTurnSignalOn: controlWindow.turnRight || controlWindow.hazardOn
    }

    SpeedGauge {
        id: speedGauge
        speed: myCar.speed

        OdoMeter {
            id: odometer
            width: 97
            height: 28
            anchors.horizontalCenter: speedGauge.horizontalCenter
            anchors.verticalCenter: speedGauge.verticalCenter
            anchors.verticalCenterOffset: 120
            font.family: "Consolas"
            font.pixelSize: 22
            visualDigits: 8
            distance: myCar.distance
        }
    }

    Image {
        id: parkingBrakeImage
        source: controlWindow.parkingBrakeOn ? "images/parkingbrake_on.png" : "images/parkingbrake_off.png"
    }

    BatteryLevel {
        id: batteryLevel
        opacity: myCar.charge > 0 ? 1.0 : 0.4
        charge: myCar.charge * 100 / myCar.maxCharge
        indicatorOn: true
        anchors.left: speedGauge.right
    }

    PowerIndicator {
        id: powerInd
        property bool powerOut: false
        enabled: myCar.powered && (myCar.charge > 0 || !powerInd.powerOut)
        opacity: powerInd.enabled ? 1.0 : 0.4
        maxValue: myCar.maxPower
        value: myCar.power
        width: 129
        height: width
        anchors.top: speedGauge.verticalCenter
        anchors.left: speedGauge.right

        states: State {
            name: "power_lost"
            when: !(myCar.charge > 0)
            }

        transitions: Transition {
            from: "*"
            to: "power_lost"
            SequentialAnimation {
                NumberAnimation {
                    target: powerInd
                    property: "value"
                    to: 0
                    duration: 500
                }
                ScriptAction {
                    script: powerInd.powerOut = true
                }
            }
        }

    }


    // --------------------------   Backend    --------------------------------------
    Car {
        id: myCar
        mass: 1000      // [kg]
        //maxSpeed: 160   // [km/h]
        maxPower: 128   // [kW]
        //distance: 0   // [m]
        maxCharge: 70   // [kwh]
        //charge: 47    // [kwh]
        powered: controlWindow.powered
        parked: controlWindow.parkingBrakeOn
        power: controlWindow.throttle / 100 * myCar.maxPower
    }

    // show the control window above the main window
    Component.onCompleted: {
        controlWindow.raise();
        controlWindow.requestActivate()
    }
}
