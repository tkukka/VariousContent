import QtQuick
import QtQuick.Controls

Column {
    property alias throttleValue : throttleSlider.value
    Text {
        text: qsTr("Throttle: ") + throttleSlider.value + "%"
        font.pixelSize: 16
    }

    Slider {
        id: throttleSlider
        from: 0
        value: 0
        to: 100
        width: 150
        stepSize: 1
        snapMode: Slider.SnapOnRelease
        handle: Rectangle {
            x: throttleSlider.leftPadding + throttleSlider.visualPosition * (throttleSlider.availableWidth - width)
            y: throttleSlider.topPadding + throttleSlider.availableHeight / 2 - height / 2
            implicitWidth: 22
            implicitHeight: 22
            radius: 11
            color: "black"
        }
        background: Rectangle {
            color: "lightgray"
        }
    }
}
