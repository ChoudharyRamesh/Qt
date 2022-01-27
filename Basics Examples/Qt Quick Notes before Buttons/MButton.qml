import QtQuick 2.0

FocusScope {
    width: 150
    height: 30
    property alias color: rectId.color
    Rectangle
    {   id:rectId
        width: parent.width
        height: parent.height
        color: "blue"
        radius: 30
        focus: true
       Text
       {
           id :textid
          anchors.centerIn: parent
           text: "default"
       }
       Keys.onPressed:
       {
           textid.text = event.key
       }
    }
}
