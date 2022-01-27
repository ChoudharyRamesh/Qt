import QtQuick
import QtQuick.Window
import Custom 1.0
import QtQuick.Controls 2.2

Window
{
    width: 250
    height: 480
    visible: true

    Rectangle
    {
        anchors.fill: parent
        anchors.margins: 50
        color: "red"

        Triangle
        {
            id:triangle
            anchors.fill: parent
            Behavior on imageRotation { NumberAnimation { duration:300}}
            Behavior on imageScaleX { NumberAnimation { duration:400}}
            Behavior on imageScaleY { NumberAnimation { duration:400}}
            property int api: GraphicsInfo.api

//            ShaderEffect
//            {
//                fragmentShader: "#version 330 core"

//            }
        }
    }


    Column
    {
        height: parent.height
        anchors.left: parent.left

        Text {
            id: label
            color: "black"
            wrapMode: Text.WordWrap
            text:
            {
                var apiStr;
                switch (triangle.api) {
                case GraphicsInfo.OpenGL: apiStr = "OpenGL (direct)"; break;
                case GraphicsInfo.Direct3D12: apiStr = "Direct3D 12 (direct)"; break;
                case GraphicsInfo.Software: apiStr = "Software (QPainter)"; break;
                case GraphicsInfo.OpenGLRhi: apiStr = "OpenGL (RHI)"; break;
                case GraphicsInfo.MetalRhi: apiStr = "Metal (RHI)"; break;
                // the example has no other QSGRenderNode subclasses
                default: apiStr = "<UNSUPPORTED>"; break;
                }
                "Custom rendering via the graphics API " + apiStr;
            }
        }

        SpinBox
        {
            from: -360
            to:360
            editable: true
            onValueChanged : triangle.imageRotation = value;
        }

        SpinBox
        {
            from: -2
            to:2
            editable: true
            stepSize: 1;
            value: 1
            onValueChanged : triangle.imageScaleX = value;
        }

        SpinBox
        {
            from: -2
            to:2
            editable: true
            stepSize: 1;
            value: 1
            onValueChanged : triangle.imageScaleY = value;
        }

        CheckBox
        {
            text: "Apply Filter"
            checked: false
            onCheckableChanged:
            {

            }
        }

    }

}
