import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import JavaApi 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("AttendanceMonitor")
    color: "black"

   Material.foreground: "cyan"
   Material.theme :Material.LightBlue
   Material.accent:  "cyan"
   Material.primary: "cyan"

    header: Rectangle
    {  width:parent.width
        height:50
        color:"blue"
        Text
        {
            text: qsTr("AttendanceMonitor")
            width: parent.width/2
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            fontSizeMode: Text.Fit
            font.pixelSize: 30
            minimumPixelSize: 1
            font.bold: true
            color: "cyan"
        }
        Image
        {
            anchors.verticalCenter: parent.verticalCenter
          anchors.right: parent.right
            width: 50
            height: 50
            source: "qrc:/icons/icons/plus.png"
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    console.log("clicked");
                    listmodel.addItem("","0","0");
                }
            }
        }
    }

    ListView
    {
        id:listview
        width: parent.width*0.95
        anchors.centerIn: parent
        height: parent.height
        delegate: delegate
        model : listmodel
        spacing: 10
    }

    JavaApi
    {
        id:javaApi
    }

    ListModel
    {
        id: listmodel

        function addItem(SubjectName,TotalClassesCount,AttendedClassesCount)
        {
            append({"SubjectName":SubjectName ,"TotalClassesCount":TotalClassesCount,"AttendedClassesCount":AttendedClassesCount })
        }

        function updateSubjectName(index,subjectName)
        {
            setProperty(index,"SubjectName", subjectName)
        }

        function updataeTotalClassesCount(index,count)
        {
            var  savedCount =parseInt(listmodel.get(index).AttendedClassesCount);
             console.log("savedCount","Count",savedCount,count)
            if(savedCount>parseInt(count))
                setProperty(index, "AttendedClassesCount", count)
            setProperty(index, "TotalClassesCount", count)
        }

        function increaseAttendedClassesCount(index)
        {
            var  savedCount =parseInt(listmodel.get(index).AttendedClassesCount);
            savedCount++;
            var totalCount = parseInt(listmodel.get(index).TotalClassesCount);
            if(savedCount<=totalCount )
                listmodel.setProperty(index, "AttendedClassesCount", savedCount.toString())
        }

        function decreaseAttendedClassesCount(index,count)
        {
            var savedCount =listmodel.get(index).AttendedClassesCount;
            savedCount--;
            console.log("savedCount",savedCount)
            if(savedCount>=0)
                listmodel.setProperty(index, "AttendedClassesCount", savedCount.toString())
        }

        Component.onCompleted:
        {
            var jsonArray  = javaApi.getData();
            for(var i=0;i<jsonArray.length;i++)
            {
                var jsonObject = jsonArray[i];
                addItem(jsonObject["SubjectName"],jsonObject["TotalClassesCount"],jsonObject["AttendedClassesCount"])
            }
        }

        Component.onDestruction:
        {
            var jsonArray = [];
             for(var i=0;i<count;i++)
             {  var jsonObject={};
                 jsonObject["SubjectName"]=listmodel.get(i).SubjectName;
                 jsonObject["TotalClassesCount"]=listmodel.get(i).TotalClassesCount;
                 jsonObject["AttendedClassesCount"]=listmodel.get(i).AttendedClassesCount;
                 jsonArray.push(jsonObject);
             }
           javaApi.updateData(JSON.stringify(jsonArray));
        }
    }

    Component
    {
        id:delegate
        Rectangle
        {
            width: listview.width
            height: 120
            radius: 10
            color: "grey"
            Row
            {
                width: parent.width-parent.width*0.04
                height: parent.height-parent.width*0.04
                anchors.centerIn: parent
                Column
                {
                    width: parent.width
                    height: parent.height
                    spacing: height*0.04

                    Rectangle
                    {
                        width: parent.width
                        height: (parent.height-2*parent.spacing)/3
                        color: "transparent"
                        Text
                        {
                            id:left
                            width: parent.width-parent.height
                            height: parent.height
                            color: "blue"
                            verticalAlignment: Text.AlignVCenter
                            fontSizeMode: Text.Fit
                            font.pixelSize: 30
                            minimumPixelSize: 1
                            text: "Subject: "+SubjectName
                        }
                        Image
                        {
                            anchors.left: left.right
                            width: parent.height
                            height: parent.height
                            source: "qrc:/icons/icons/up.png"
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    listmodel.increaseAttendedClassesCount(index)
                                }
                            }
                        }
                    }

                    Rectangle
                    {
                        width: parent.width
                        height: (parent.height-2*parent.spacing)/3
                        color: "transparent"
                        Text
                        {  id:leftrec
                            width: parent.width-parent.height
                            height: parent.height
                            color: "blue"
                            verticalAlignment: Text.AlignVCenter
                            fontSizeMode: Text.Fit
                            font.pixelSize: 30
                            minimumPixelSize: 1
                            text:"Attendance : "+AttendedClassesCount+"/"+TotalClassesCount;
                        }
                        Image
                        {
                            anchors.left: leftrec.right
                            width: parent.height
                            height: parent.height
                            source: "qrc:/icons/icons/down.png"
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    listmodel.decreaseAttendedClassesCount(index)
                                }
                            }
                        }
                    }

                    Rectangle
                    {
                        width: parent.width
                        height: (parent.height-2*parent.spacing)/3
                        color: "transparent"
                        Rectangle
                        {
                            width: parent.width/3
                            height: parent.height
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width/12;
                            color: "cyan"
                            radius: 10
                            Text
                            {
                                anchors.fill:parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.Fit
                                font.pixelSize: 40
                                minimumPixelSize: 1
                                text: "Edit"
                            }
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    editDialog.openDialog(index,SubjectName,TotalClassesCount);
                                }
                            }
                        }
                        Rectangle
                        {
                            width: parent.width/3
                            height: parent.height
                            anchors.right: parent.right
                            anchors.rightMargin:parent.width/12;
                            color: "cyan"
                            radius: 10
                            Text
                            {
                                anchors.fill:parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.Fit
                                font.pixelSize: 40
                                minimumPixelSize: 1
                                text: "Delete"
                            }
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    listmodel.remove(index);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Dialog
    {
        id:editDialog
      //  anchors.centerIn: parent
        title: "Edit"
        width: parent.width*0.6
        height: 230
        x:(parent.width-width)/2
        y:(parent.height/2)-height
        property int currentIndex:-1
        standardButtons: Dialog.Ok | Dialog.Cancel
        closePolicy: Popup.CloseOnEscape
        modal: true
        dim: false
        background: Rectangle{ color:"white"}


        TextField
        {
            id:subjectInputId
            width: parent.width*0.9
            height: 50
            color: "blue"
            placeholderText: "Subject Name"
            placeholderTextColor: "grey"
        }

        TextField
        {
            id:toatalAttendanceId
            width: parent.width*0.9
            anchors.top: subjectInputId.bottom
            anchors.topMargin: 5
            height: 50
            color: "blue"
            placeholderText: "Total Classes"
            placeholderTextColor: "grey"
            inputMethodHints :Qt.ImhDigitsOnly
            validator: IntValidator { bottom:0; top: 1000;}
        }

        function openDialog(index,subjectName,totalAttendence)
        {
            subjectInputId.text=subjectName;
            toatalAttendanceId.text=totalAttendence;
            currentIndex= index;
            console.log(currentIndex,index);
            open();
        }
        onAccepted:
        {
            listmodel.updateSubjectName(currentIndex,subjectInputId.text);
            listmodel.updataeTotalClassesCount(currentIndex,toatalAttendanceId.text)
            currentIndex=-1
        }
    }
}
