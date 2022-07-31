import QtQuick
import QtQuick.Window
import Custom 1.0

Window {
    width: 500
    height: 500
    visible: true
    title: qsTr("Hello World")

    Timer
    {
        repeat: true
        interval: 15
        running: true
        onTriggered: cube.update();
    }

    Rectangle
    {
        anchors.fill: parent
        color: "red"
        Cube
        {
            id:cube
            anchors.fill: parent
            Text
            {
                text: "hello world"
                color: "white"
            }
        }
    }

}
