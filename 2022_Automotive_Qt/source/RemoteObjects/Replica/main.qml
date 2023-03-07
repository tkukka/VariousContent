import QtQuick
import Replica
Window {
    id: window
    width: gaugeImg.width
    height: gaugeImg.height
    visible: true
    title: qsTr("[Replica]")

    Image {
        id: gaugeImg
        source: "images/Gauge.png"
        anchors.centerIn: window.contentItem
        MouseArea {
            id: mouseImg
            anchors.fill: gaugeImg
            onClicked: Dashboard.test()
        }
    }

    Rectangle {
        id: rect1
        color: "black"
        width: text1.width
        height: text1.height

    }

    Text {
        id: text1
        color: "white"
        font.pixelSize: 22
        text: qsTr("Click the picture")
        anchors.centerIn: rect1
    }
}
