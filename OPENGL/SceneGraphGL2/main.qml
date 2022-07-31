import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        anchors.fill: parent
        layer.enabled: true
        layer.effect:  ShaderEffect
        {
            // vertexShader: "/Shaders/vertexShader.vert.qsb"
            fragmentShader: "/Shaders/fragmentShader.frag.qsb"
        }
    }



}
