import QtQuick 2.0

Item {
    height: 30
    width:120
    //public properties
    property string buttoncolorOnReleased : "blue"
    property string buttontext : "Click me"
    property string buttoncolorOnPressed : "aqua"
    Rectangle
    {   property string currentButtonColor : buttoncolorOnReleased
        id:rectanglee
        radius: 30
        anchors.fill: parent
        color: currentButtonColor
        Text {
            id: buttonTextId
            text: buttontext
            anchors.centerIn: parent
            color: "white"
        }
        MouseArea
        {
            anchors.fill: parent
             onPressed:
             {
                rectanglee.currentButtonColor =buttoncolorOnPressed
             }
             onReleased:
             {
                rectanglee.currentButtonColor = buttoncolorOnReleased
             }
        }
    }

}
