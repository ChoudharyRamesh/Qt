import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtMultimedia 5.15
import QImageFilters 1.0
import "."

ApplicationWindow
{
    id:rootwindow
    visible: true
    width:  703
    height: 790

    Camera
    {
        id: camera
        objectName: "camera"
        captureMode: Camera.CaptureStillImage
        exposure
        {
            exposureMode: Camera.ExposureAuto
        }

        focus
        {
            focusMode: Camera.FocusContinuous
            focusPointMode: Camera.FocusPointCenter
        }
    }


    VideoOutput
    {
        id:videooutput
        width: parent.width
        height: parent.height/2
        anchors.top: parent.top
        source: camera
        autoOrientation: true
        filters: [ edgeFilter  ]

        Rectangle
        {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            width: 50
            height: 50
            radius: 50
            color: "red"
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    if(camera.position===Camera.FrontFace)
                        camera.position=Camera.BackFace
                    else camera.position= Camera.FrontFace
                }
            }
        }
    }

    EdgeFilter
    {
        id:edgeFilter
    }


    VideoProducer
    {
        id:myvideoProducer
        Component.onCompleted:
        {
            edgeFilter.setVideoProducer(this);
            videooutput2.source=this;
        }
    }


    VideoOutput
    {
        id:videooutput2
        width: parent.width
        height: parent.height/2
        anchors.bottom: parent.bottom
        orientation: -90
    }
}
