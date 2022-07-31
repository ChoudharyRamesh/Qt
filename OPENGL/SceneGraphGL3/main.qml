import QtQuick
import CustomItem 1.0
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    CustomItem {
        property real t: 1
        anchors.fill: parent
        center: Qt.point(-0.748, 0.1);
        iterationLimit: 3 * (zoom + 30)
        zoom: t * t / 10
        NumberAnimation on t {
            from: 1
            to: 60
            duration: 30*1000;
            running: true
            loops: Animation.Infinite
        }
    }
}
