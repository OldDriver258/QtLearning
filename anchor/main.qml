import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    width: 220
    height: 220
    visible: true
    color: "black"

    GreenRectangle {
        x: 10
        y: 10
        width: 100
        height: 100
        BlueRectangle {

//            width: 12
//            anchors.fill: parent
//            anchors.margins: 8

//            width: 48
//            y: 8
//            anchors.left: parent.left
//            anchors.leftMargin: 8

//            width: 48
//            anchors.left: parent.right

            id: blue
            width: 48
            height: 24
            y: 8
            anchors.horizontalCenter: parent.horizontalCenter
        }

        BlueRectangle {
            id: blue2
            width: 72
            height: 24
            anchors.top: blue.bottom
            anchors.topMargin: 4
            anchors.horizontalCenter: blue.horizontalCenter
        }
    }

}
