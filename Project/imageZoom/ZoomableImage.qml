import QtQuick 2.15

Flickable
{
    id:flickable
    property alias source: mImage.source
    onWidthChanged:resetScale(false);
    onHeightChanged: resetScale(false);
    contentWidth :  privateProperties.imageWidth;
    contentHeight : privateProperties.imageHeight;
    boundsBehavior: scaleNumberAnimation.running ? Flickable.StopAtBounds : Flickable.DragAndOvershootBounds
    boundsMovement: scaleNumberAnimation.running ? Flickable.StopAtBounds : Flickable.FollowBoundsBehavior
    interactive: privateProperties.currentZoomFactor===1 ? false  : true;

    states: [
        State {
            name: "state_StickToCenter" // state is used when content size is less than flickable size then content
            // center should stick to flickable center
            when : ( flickable.contentWidth < flickable.width || flickable.contentHeight< flickable.height )
            PropertyChanges {
                target: flickable.contentItem
                anchors.horizontalCenter:  width < flickable.width ? flickable.horizontalCenter : undefined
                anchors.verticalCenter:   height < flickable.height ? flickable.verticalCenter : undefined
            }
        }
    ]
    onStateChanged: { cancelFlick(); returnToBounds(); }

    Image
    {
        id:mImage
        width:flickable.contentWidth;
        height: flickable.contentHeight;
        source: flickable.imageSource
        asynchronous: true
        autoTransform: true
        fillMode: Image.PreserveAspectFit;
        onSourceChanged: privateProperties.canCalculateImageAspect = true;

        Rectangle
        {
            anchors.fill: parent
            color: "transparent"
            border.width: 3;
            border.color: "green"
        }


        onPaintedGeometryChanged:
        {
            if(paintedHeight!=0 && paintedWidth!=0)
            {
                var ratio = paintedWidth/paintedHeight;
                ratio = (ratio).toFixed(3);
                privateProperties.imageAspectRatio = ratio;
            }
        }

        PinchArea
        {
            id:pinchArea
            anchors.fill: parent
            property bool zoomTriggeredFromPinchArea:false
            property point pinchCenter;

            onPinchStarted: zoomTriggeredFromPinchArea=true;
            onPinchUpdated:
            {
                var newZoomFactor = privateProperties.currentZoomFactor+ privateProperties.currentZoomFactor*(pinch.scale-1);
                pinchCenter =pinch.center;
                privateProperties.zoom(privateProperties.getBoundedScaleFactor(newZoomFactor))
            }

            onPinchFinished:
            {
                privateProperties.currentZoomFactor +=  privateProperties.currentZoomFactor*(pinch.scale-1);
                privateProperties.currentZoomFactor = privateProperties.getBoundedScaleFactor(privateProperties.currentZoomFactor);
                zoomTriggeredFromPinchArea=false;
            }

            MouseArea
            {
                id:mouseArea
                anchors.fill: parent
                onReleased: mouse.accepted= false;
                propagateComposedEvents :true
                scrollGestureEnabled: true
                hoverEnabled: true

                onDoubleClicked:
                {
                    mouse.accepted=false;
                    if(privateProperties.currentZoomFactor>1)resetScale();
                    else
                    {
                        var widthScale = (flickable.width+20)/mImage.width;
                        var heightScale = (flickable.height+20)/mImage.height;
                        var maxScale = Math.max(widthScale,heightScale);
                        if(maxScale>1)
                        {
                            privateProperties.pointOfDoubleClick = Qt.point(mouseX,mouseY);
                            privateProperties.useDoubleClickPoint = true;
                            privateProperties.currentZoomFactor = maxScale;
                        }
                    }
                }

                onWheel:
                {
                    if(wheel.modifiers===Qt.ControlModifier)
                    {
                        wheel.accepted=true;
                        var newZoomFactor;
                        if(wheel.angleDelta.y>0)
                            newZoomFactor = privateProperties.currentZoomFactor + (privateProperties.currentZoomFactor*privateProperties.zoomStepFactor);
                        else  newZoomFactor = privateProperties.currentZoomFactor - (privateProperties.currentZoomFactor*privateProperties.zoomStepFactor);
                        privateProperties.currentZoomFactor = privateProperties.getBoundedScaleFactor(newZoomFactor);
                        return;
                    }
                    wheel.accepted=false;
                }
            }


        }
    }

    QtObject
    {
        id : privateProperties
        property real imageAspectRatio :1
        property bool canCalculateImageAspect : true
        property real imageWidth : getAspectWH(flickable.width*0.8, flickable.height*0.8,imageAspectRatio).width;
        property real imageHeight :  getAspectWH(flickable.width*0.8,flickable.height*0.8, imageAspectRatio).height;
        property bool useDoubleClickPoint:false;
        property point pointOfDoubleClick;
        property real maxZoomFactor : 30.0
        property real zoomStepFactor :0.3;
        property real currentZoomFactor: 1
        property real minZoomFactor :1;
        property point scaleCenter : pinchArea.zoomTriggeredFromPinchArea
                                     ? pinchArea.pinchCenter : Qt.point(mouseArea.mouseX,mouseArea.mouseY);
        Behavior on currentZoomFactor {
            NumberAnimation { id:scaleNumberAnimation
                duration: pinchArea.zoomTriggeredFromPinchArea
                          ? 0 : privateProperties.useDoubleClickPoint ?
                                Math.min(200*privateProperties.currentZoomFactor,500) : 200 ;
                onRunningChanged:  if(!running) privateProperties.useDoubleClickPoint=false;
            }
        }

        function getAspectWH(width,height,ratio)
        {
            var copyW = width;
            var copyH = height;
            if(ratio>1)
            {
                height = width/ratio;
                if(height>copyH)
                {
                    height = copyH;
                    width = ratio*height;
                }
            }
            else
            {
                width = height*ratio;
                if(width>copyW)
                {
                    width = copyW;
                    height = width/ratio;
                }
            }
            return {"width":width,"height":height};
        }


        onCurrentZoomFactorChanged :
            if(!pinchArea.zoomTriggeredFromPinchArea)zoom(currentZoomFactor);

        function zoom(scaleFactor)
        {
            var targetWidth =  privateProperties.imageWidth*scaleFactor;
            var targetHeight  = privateProperties.imageHeight*scaleFactor;
            if(useDoubleClickPoint) resizeContent(targetWidth,targetHeight,mapToItem(mImage,pointOfDoubleClick));
            else resizeContent(targetWidth,targetHeight,scaleCenter);
            returnToBounds();
        }

        function getBoundedScaleFactor(ScaleFactor)
        {
            if(ScaleFactor>maxZoomFactor)ScaleFactor = maxZoomFactor;
            else if(ScaleFactor<minZoomFactor)ScaleFactor = minZoomFactor;
            return ScaleFactor;
        }
    }

    function resetScale(animated=true)
    {
        if(animated)
        {
            privateProperties.pointOfDoubleClick = Qt.point(0,0);
            privateProperties.useDoubleClickPoint = true;
            privateProperties.currentZoomFactor = 1;
        }
        else
        {
            pinchArea.zoomTriggeredFromPinchArea =true;
            privateProperties.currentZoomFactor = 1;
            pinchArea.pinchCenter = Qt.point(0,0);
            privateProperties.zoom(1);
            pinchArea.zoomTriggeredFromPinchArea=false;
        }
    }

}
