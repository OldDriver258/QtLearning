import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 360
    height: 360
    visible: true
    title: qsTr("Hello World")
    Text {
        anchors.centerIn: parent
        id: label
        //定义按下空格次数的属性
        property int spacePresses: 0
        text: "Space pressed: " + spacePresses + " times"
        //响应函数
        onTextChanged: console.log("text changed to: ", text)
        //接受事件设置 focus 属性
        focus: true
        //设置按键出发事件
        Keys.onSpacePressed: {
            increment()
        }
        Keys.onEscapePressed: {
            label.text = ' ';
        }
        //自定义函数
        function increment() {
            spacePresses += 1
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
