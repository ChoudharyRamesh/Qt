import QtQuick
import QtMultimedia

Rectangle {
    width: 800
    height: 480

    CaptureSession{
        camera: Camera{
            active: true
        }
        videoOutput: videOutput
    }

    VideoOutput{
        anchors.fill: parent
        id:videOutput
    }
}

