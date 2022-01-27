import QtQuick 2.15
import QtQuick.Window 2.15
import Temp 1.0

Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color:"black"

    Column
    {
        anchors.fill: parent
        spacing: 10

        Rectangle
        {
            width: parent.width*0.95
            height: 50
            radius: 10
            color: "red"
            MouseArea
            {
                anchors.fill:parent
                onClicked:
                {
                    temp.showBannerAd();
                    console.log("########### clicked")
                }
            }
        }

        Rectangle
        {
            width: parent.width*0.95
            height: 50
            radius: 10
            color: "blue"
            MouseArea
            {
                anchors.fill:parent
                onClicked:
                {
                    temp.hideBannerAd();
                    console.log("########### clicked")
                }
            }
        }

//      //back key handle
//       focus: true
//       Keys.enabled: true
//       Keys.onReleased: {
//            if(event.key===Qt.Key_Back)
//           {
//               event.accepted = true
//               console.log("back key captured in main window qml")
//               temp.hideInterstitialAd();
//           }
//       }
    }

    Temp
    {
        id:temp
    }

}
