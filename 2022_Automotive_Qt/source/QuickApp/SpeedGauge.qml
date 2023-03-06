import QtQuick
Item {
    id: root
    property double speed: 0

    width: speedGaugeImg.width
    height: speedGaugeImg.height
    Image {
        id: speedGaugeImg
        source: "images/speedgauge.png"

        Image {
            id: needleYellowImg
            source: "images/needleyellow.png"
            transformOrigin: Item.Bottom
            rotation: -136 + root.speed/260 * 272
            anchors.horizontalCenter: speedGaugeImg.horizontalCenter
            anchors.verticalCenter: speedGaugeImg.verticalCenter
            anchors.verticalCenterOffset: -height * 0.5
        }
        Image {
            id: centerCover
            source: "images/gaugeCenterBig.png"
            anchors.centerIn: speedGaugeImg
        }
    }

    // smooth needle rotation
    Behavior on speed {
        NumberAnimation {}
    }


}

