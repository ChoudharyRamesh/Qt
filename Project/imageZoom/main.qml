import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id:rootWindow
    width: 800
    height: 800
    visible: true
    y:40
    x:1110
    title: qsTr("Hello World")
    // flags: Qt.WindowStaysOnTopHint
    Rectangle
    {
        anchors.fill: parent
        color: "black"
    }


    //    Rectangle
    //    {
    //        anchors.fill: parent
    //        color: "transparent";
    //        border.width: 3
    //        border.color: "red"
    //        focus: true
    //        Keys.onPressed:
    //        {
    //            if(event.key===Qt.Key_R)
    //            {
    //                rootWindow.close();
    //                liveClient.loadQml();
    //            }
    //            else if(event.key===Qt.Key_Escape)
    //            {
    //                if(rootWindow.y===1080)
    //                    rootWindow.y=0;
    //                else rootWindow.y=1080;
    //            }
    //        }

    //        Rectangle
    //        {
    //            width: getAspectWH(parent.width,parent.height,1.6).width;
    //            height: getAspectWH(parent.width,parent.height,1.6).height;
    //            anchors.centerIn: parent;
    //            color: "red"
    //            border.width: 5
    //            border.color: "blue"

    //            function getAspectWH(width,height,ratio)
    //            {
    //                var copyW = width;
    //                var copyH = height;
    //                if(ratio>1)
    //                {
    //                    height = width/ratio;
    //                    if(height>copyH)
    //                    {
    //                        height = copyH;
    //                        width = ratio*height;
    //                    }
    //                }
    //                else
    //                {
    //                    width = height*ratio;
    //                    if(width>copyW)
    //                    {
    //                        width = copyW;
    //                        height = width/ratio;
    //                    }
    //                }

    //                //console.log("width",copyW,"height",copyH,"AspectWidth",width,"AspectHeight",height,"ratio",ratio)
    //                return {"width":width,"height":height};
    //            }
    //        }

    //    }



    SwipeView
    {
        id:swipeView
        //        width: 600
        //        height: 600
        //        anchors.centerIn: parent
        anchors.fill: parent
        focus: true
        onCurrentItemChanged:
        {
            interactive = Qt.binding(function(){ return !currentItem.children[0].interactive; })
        }

        Repeater {
            model: 15
            Loader{
                asynchronous: true
                active: true
                sourceComponent: ZoomableImage
                {
                    source : "qrc:/image/myImage.jpg"
                }
            }
        }

        Keys.onPressed:
        {
            if(event.key===Qt.Key_R)
            {
                rootWindow.close();
                liveClient.loadQml();
            }
            else if(event.key===Qt.Key_Escape)
            {
                if(rootWindow.y===1080)
                    rootWindow.y=0;
                else rootWindow.y=1080;
            }
        }
    }
    Rectangle
    {
        anchors.fill: swipeView
        anchors.centerIn: parent
        color: "transparent";
        border.width: 3
        border.color: "red"
    }

}
