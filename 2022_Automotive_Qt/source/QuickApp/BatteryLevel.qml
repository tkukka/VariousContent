import QtQuick

Item {
    id: root
    property double charge
    property bool indicatorOn: false
    property color levelColor: "black"

    width: column.width
    height: column.height

    Column {
        id: column
        spacing: 5
        Image {
            id: batteryImg
            source: "images/Icon_Battery_OFF.png"
        }

        Rectangle {
            id: levelRect
            anchors.horizontalCenter: batteryImg.horizontalCenter
            width: 40
            height: 110
            color: "black"
            Rectangle {
                anchors.bottom: levelRect.bottom
                anchors.bottomMargin: 5
                anchors.horizontalCenter: levelRect.horizontalCenter
                width: levelRect.width * 0.8
                height: charge
                color: levelColor

            }
        }

        Rectangle {
            id: percentageRect
            width: 80
            height: 34
            color: "black"
            Text {
                text: charge.toFixed() + "%"
                color: levelColor
                font.pixelSize: 30
                anchors.centerIn: percentageRect
            }
        }

    }

    onIndicatorOnChanged: {

        if (!indicatorOn) {
            levelColor = "black"
            batteryImg.source = "images/Icon_Battery_OFF.png"
        }
        else {
            root.chargeChanged()
        }
    }

    onChargeChanged:  {

        if (!indicatorOn) {
            return
        }

        if (charge >= 65) {
            levelColor = "green"
            batteryImg.source = "images/Icon_Battery_Green.png"
        }
        else if (charge >= 15 && charge < 65) {
            levelColor = "yellow"
            batteryImg.source = "images/Icon_Battery_Yellow.png"
        }
        else if (charge >= 0 && charge < 15){
            levelColor = "red"
            batteryImg.source = "images/Icon_Battery_Red.png"
        }
    }
}
