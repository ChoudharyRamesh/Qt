import QtQuick 2.0

Rectangle
{
    width:400
    height: 400
    anchors.centerIn: parent
    layer.enabled: true
    layer.effect: ShaderEffect
    {
        fragmentShader:"qrc:/SceneGraphGL3/Shaders/shader.frag.qsb"
    }
}
