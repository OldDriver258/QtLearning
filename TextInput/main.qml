import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 200
    height: 80
    visible: true

    LineEdit {
        id: input1
        x: 8; y: 8
        width: 96
        height: 20
        focus: true
        text: "Text Input 1"
        KeyNavigation.tab: input2
    }


    LineEdit {
        id: input2
        x: 8; y: 36
        width: 96
        height: 20
        focus: true
        text: "Text Input 2"
        KeyNavigation.tab: input1
    }
}
