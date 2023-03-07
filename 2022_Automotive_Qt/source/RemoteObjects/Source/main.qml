import QtQuick
import Source

Window {
    id: window
    width: carImg.width
    height: carImg.height
    visible: true
    title: qsTr("[Source]")

    Image {
        id: carImg
        source: "images/Car.png"
        anchors.centerIn: window.contentItem
        MouseArea {
            id: mouseImg
            anchors.fill: carImg
            onPressed: Controller.start()
        }
    }

    Text {
        font.pixelSize: 44
        color: "black"
        text: qsTr("Click the picture");
        anchors.horizontalCenter: carImg.horizontalCenter
    }

}
