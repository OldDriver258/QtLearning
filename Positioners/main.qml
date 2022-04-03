import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true

    Rectangle {
        id: root1
        width: 120
        height: 240
        color: "black"

        Column {
            id: column
            anchors.centerIn: parent
            spacing: 8
            RedRectangle {}
            GreenRectangle {width: 96}
            BlueRectangle {}
        }
    }

    Rectangle {
        id: root2
        x: root1.width
        width: 240
        height: 120
        color: "black"

        Row {
            id: row
            anchors.centerIn: parent
            spacing: 8
            RedRectangle {}
            GreenRectangle {width: 96}
            BlueRectangle {}
        }
    }

    Rectangle {
        id: root3
        x: root1.width + root2.width
        width: 200
        height: 200
        color: "black"

        Grid {
            id: grid
            rows: 2
            anchors.centerIn: parent
            spacing: 8
            RedRectangle { }
            RedRectangle { }
            RedRectangle { }
            RedRectangle { }
            RedRectangle { }
        }
    }

    Rectangle {
        id: root4
        x: root1.width + root2.width + root3.width
        width: 160
        height: 160
        color: "black"

        Flow {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 20
            RedRectangle { }
            BlueRectangle { }
            GreenRectangle { }
        }
    }

    Rectangle {
        id: root
        y: 240
        width: 252
        height: 252
        color: "black"
        property variant colorArray: ["#00bde3", "#67c111", "#ea7025"]

        Grid {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 4
            Repeater {
                model: 16
                Rectangle {
                    width: 56; height: 56
                    property int colorIndex: Math.floor(Math.random()*3)
                    color: root.colorArray[colorIndex]
                    border.color: Qt.lighter(color)
                    Text {
                        anchors.centerIn: parent
                        color: "black"
                        text: "Cell " + index
                    }
                }
            }
        }
    }
}
