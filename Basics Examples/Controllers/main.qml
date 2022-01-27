import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import QtQuick.XmlListModel 2.12

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400


}




/*
Window
{
   id : rootWindow
   visible :true
   height: 800
   width : 800
   title: "Buttons"

   RowLayout
     {
         width:parent.width
         height: 50
         Button
         {
           id:button1
           Layout.fillHeight: true
           text: "button1"
           Layout.fillWidth: true
           onClicked:
           {
               console.log("button one is clicked")
           }
         }
         Button{
          id:button2
            text: "button1"
          Layout.fillHeight: true
          Layout.fillWidth: true
          onClicked:
          {
              console.log("button two is clicked")
          }
         }
     }


}
*/




/*

Window
{
   id : rootWindow
   visible :true
   height: 200
   width : 400
   title: "Busy indicator"

   ColumnLayout
   {  anchors.fill: parent

       BusyIndicator
       {  id: busyindactor1
           width: parent.width
          Layout.alignment: Qt.AlignCenter
       }
       ColumnLayout
       {  width: parent.width
           Button
           {   width: parent.width
               id:buttonid1
               Layout.fillWidth: true
               text: "Running"
               onClicked:
                {
                    busyindactor1.running=true;
                   busyindactor1.visible=true;
                }
           }
           Button
           {    width: parent.width
                Layout.fillWidth: true
                 id:buttonid2
                 text:"Not running"
                 onClicked:
                 {
                    busyindactor1.running=false;
                    busyindactor1.visible=false;
                 }
           }
       }
   }


}


*/



/*

Window
{
   id : rootWindow
   visible :true
   height: 200
   width : 400
   title: "Check box demo"

   Column
   {
       spacing: 20
       anchors.horizontalCenter: parent.horizontalCenter
       CheckBox
       {
           id:checkbox1
           text: "Option1"
           onCheckStateChanged:
           {
               if(checked ===true) console.log("option 1 is checked")
               else  console.log("option 1 is Unchecked")
           }
       }
       CheckBox
       {
           id:checkbox2
           text: "Option2"
           onCheckStateChanged:
           {
               if(checked===true) console.log("option 2 is checked")
               else  console.log("option 2 is Unchecked")
           }
       }
       CheckBox
       {
           id:checkbox3
           text: "Option3"
           onCheckStateChanged:
           {
              if(checked===true) console.log("option 3 is checked")
              else  console.log("option 3 is Unchecked")
           }
       }
   }
}


*/


/*
Window
{
   id : rootWindow
   visible :true
   height: 400
   width : 200
   title: "Combo box demo"

   Column
   {
       spacing: 20
       width: parent.width
       anchors.horizontalCenter: parent.horizontalCenter
       Label
       {
           text: "MyLabel"
           wrapMode: "Wrap"
           width: parent.width
           horizontalAlignment: Qt.AlignHCenter
       }
       ComboBox
       {
           id:comboBox1
           anchors.horizontalCenter: parent.horizontalCenter
           model:["one","two","three","four"]
           editable: true
           onActivated:
           {
               console.log(comboBox1.currentValue)
           }
       }
   }

}

*/

/*
Window
{
   id : rootWindow
   visible :true
   height: 400
   width : 200
   title: "Delay Button demo"

   Column
   {
       spacing: 20
       width: parent.width
       anchors.horizontalCenter: parent.horizontalCenter
       Label
       {
           text: "MyLabel"
           wrapMode: "Wrap"
           width: parent.width
           horizontalAlignment: Qt.AlignHCenter
       }
       DelayButton
       {
           id:deleaybutton1
           anchors.horizontalCenter: parent.horizontalCenter
           text:"DelayButton"
           delay: 1000
           onActivated:
           {
               console.log("activated")
           }
           onProgressChanged:
           {
               console.log(progress)
           }
       }
   }

}

*/

/*
Window
{
   id : rootWindow
   visible :true
   height: 400
   width : 200
   title: "Dial demo"

   Column
   {
       spacing: 20
       width: parent.width
       anchors.horizontalCenter: parent.horizontalCenter
       Label
       {
           text: "MyLabel"
           wrapMode: "Wrap"
           width: parent.width
           horizontalAlignment: Qt.AlignHCenter
       }
       Dial
       {
           id:deleaybutton1
           from: 1
           to:100
           anchors.horizontalCenter: parent.horizontalCenter
           onValueChanged:
           {
               console.log(value)
           }
       }
   }

}
*/

/*
Window
{
   id : rootWindow
   visible :true
   height: 400
   width : 200
   title: "Frame demo"  // used for grouping element

   Column
   {
       spacing: 20
       width: parent.width
       anchors.horizontalCenter: parent.horizontalCenter
       Label
       {
           text: "MyLabel"
           wrapMode: "Wrap"
           width: parent.width
           horizontalAlignment: Qt.AlignHCenter
       }
       Frame
       {  spacing: 2
           width: parent.width
           anchors.horizontalCenter: parent.horizontalCenter
           id:frame1
           Column
           {
               spacing: 2
               width: parent.width
               anchors.horizontalCenter: parent.horizontalCenter
               Button
               {

               }
               Button
               {

               }
               Button
               {

               }
           }
       }
   }

}
*/

/*

Window
{
   id : rootWindow
   visible :true
   height: 400
   width : 200
   title: "GroupBox demo"

   Column
   {
       spacing: 20
       width: parent.width
       anchors.horizontalCenter: parent.horizontalCenter
       Label
       {
           text: "MyLabel"
           wrapMode: "Wrap"
           width: parent.width
           horizontalAlignment: Qt.AlignHCenter
       }

       GroupBox // not only visual grouping like frame but it provide some extra features
       {
           title: "choose item"
           anchors.horizontalCenter: parent.horizontalCenter
           Column
           {
               RadioButton
               {
                   text:"one"
               }
               RadioButton
               {
                   text:"two"
               }
               RadioButton
               {
                   text:"three"
               }
           }
       }
   }

}
*/

/*
Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "page indicator and swipe view demo"

   SwipeView
   {
       id:swipeviewid
       anchors.fill:parent
       currentIndex: pageindicatorid.currentIndex

       Image
       {
           id: image1
           source: "https://images.pexels.com/photos/60597/dahlia-red-blossom-bloom-60597.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500"
       }
       Image
       {
           id: image2
           source: "https://images.pexels.com/photos/68147/waterfall-thac-dray-nur-buon-me-thuot-daklak-68147.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500"
       }
       Image
       {
           id: image3
           source: "https://images.pexels.com/photos/462118/pexels-photo-462118.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500"
       }
   }

   PageIndicator
      {
          id:pageindicatorid
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.bottom: swipeviewid.bottom

          //page indicator specific properties
          currentIndex: swipeviewid.currentIndex
          interactive: true
          count:swipeviewid.count

      }

}

*/


/*
Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "ProgressBar  Demo"

   ProgressBar
   {
       anchors.centerIn: parent
       id:progress1
       width: 300
       from:1
       smooth: true
       to:100
      onValueChanged:
      {
         console.log(value)
          if(value===100)value=0;
      }
   }

   MouseArea
   {
       anchors.top: progress1.bottom
       anchors.left: progress1.left
       height: 500
       width:500
       onClicked:
       {
           progress1.value =  progress1.value+10
       }
   }
}
*/

/*
Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Rangel Slider Demo"

      RangeSlider
      {  width:parent.width-parent.width/8
          anchors.centerIn: parent
          spacing: 30
          from:1; to :100
          first.value: 0; second.value: 100;
          first.onValueChanged:
          {
              console.log("first value changed to "+first.value)
          }
          second.onValueChanged:
          {
               console.log("second value changed to "+second.value)
          }
      }

}
*/



/*

Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Flicable and ScrollBar Demo"

   Flickable
   {
       width: parent.width
       height: parent.height
       contentHeight: columnid.implicitHeight
       ScrollBar.vertical: ScrollBar  // spawn scrollbar
       {
           width:5
       }

       Column
       {
           id:columnid
           spacing: 5
           anchors.fill: parent

           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "1"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "2"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "3"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "4"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "5"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "6"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "7"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "8"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "9"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "10"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "11"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "12"
               }
           }
           Rectangle
           {
               width:parent.width
               height: 50
               radius: 30
               color: "red"
               Text {
                   font.pointSize: 15
                   anchors.centerIn: parent
                   text: "13"
               }
           }
       }
   }

}

*/

/*

Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Slider Demo"  // similar as RangeSlider except it has only on slider

    Slider
    { id:slider1
        width: parent.width-(parent.width/10)
        anchors.centerIn: parent
        onValueChanged:
        {
           progressBar.value=slider1.value
        }
    }

    ProgressBar
    {
        id:progressBar
        width:slider1.width-12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top:slider1.bottom
    }

}

*/


/*
Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Switch Demo"

Column
{
    width:parent.width
    anchors.fill:parent
    Switch
    {
       anchors.horizontalCenter: parent.horizontalCenter
        text: "Hotspot"
        onCheckedChanged:
        {
            if(checked===true)
                console.log("checked")
            else console.log("not checked")
        }
    }
}

}
*/


/*

Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Page Tab bar Demo"

   Page
   {
       id:pageid
       anchors.fill: parent
       SwipeView
       {
           id:swipeview
           anchors.fill: parent
           currentIndex: tab1.currentIndex
           Image
           {
               id: image1
               source: "https://images.pexels.com/photos/60597/dahlia-red-blossom-bloom-60597.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500"
           }
           Image
           {
               id: image2
               source: "https://images.pexels.com/photos/68147/waterfall-thac-dray-nur-buon-me-thuot-daklak-68147.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500"
           }
           Image
           {
               id: image3
               source: "https://images.pexels.com/photos/462118/pexels-photo-462118.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500"
           }
       }

       header: Label
       {
             text :"Header"
       }

       footer:TabBar
       {
           id:tab1
           currentIndex:swipeview.currentIndex

           TabButton
           {
               text: "first"
           }
           TabButton
           {
               text: "second"
           }
           TabButton
           {
               text: "third"
           }
       }
   }

}

*/


/*

Window
{
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Text Area Demo"

  Label
  {  id:label
      width: parent.width
      wrapMode: Label.Wrap
      height: 20
      horizontalAlignment: Qt.AlignHCenter
      text:"Text Area Multiline editor"
  }

  ScrollView
  {  width: parent.width
      anchors.top:label.bottom
      height: parent.height-label.height
      contentHeight: textarea.implicitHeight
    TextArea
      {  width: parent.width
          height: parent.height
          id:textarea
          background: Rectangle {   color:"cyan"  }
          font.pointSize: 20
          color: "black"
          text: "a\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\n\
a\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\na\n"
          wrapMode: TextArea.Wrap
          selectByMouse: true
       }
   }
}


*/


/*

Window
{
    id : rootWindow
    visible :true
    height: 600
    width : 600
    title: "Text Field Demo"

    Column
    {
        anchors.fill: parent
        Row
        {
            id:row1
            width: parent.width
            spacing: 10
            height: 40
            Label
            {
                id:label1
                height: 40
                width: 100
                text:"First Name"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            TextField
            {
                id:texxtfield1
                height: 40
                width: 100
            }
        }
        Row
        {
            id:row2
            width: parent.width
            spacing: 10
            height: 40
            Label
            {
                id:label2
                height: 40
                width: 100
                text:"Last Name"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            TextField
            {
                id:texxtfield2
                height: 40
                width: 100
                onTextChanged:
                {
                    console.log(text)
                }
            }
        }
    }
}

*/


/*

Window
{
    id : rootWindow
    visible :true
    height: 600
    width : 600
    title: "Split view demo"  // splitting in android touch problem

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal


         Rectangle {
             implicitWidth: 200
             SplitView.maximumWidth: 400
             color: "lightblue"
             Label
             {
                 text: "View 1"
                 anchors.centerIn: parent
             }
         }
         Rectangle {
             id: centerItem
             SplitView.minimumWidth: 50
             SplitView.fillWidth: true
             color: "#00ffff"
             Label {
                 text: "View 2"
                 anchors.centerIn: parent
             }
         }
         Rectangle {
             implicitWidth: 200
             color: "lightgreen"
             Label {
                 text: "View 3"
                 anchors.centerIn: parent
             }
         }
     }
}

*/

/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Drawer demo"  // splitting in android touch problem
      header: ToolBar
      {  width:parent.width
          height:toolbutton.implicitHeight
          background: Rectangle
          {
              color :  "cyan"
          }
          RowLayout
          {
              spacing: 10
              ToolButton
              {  id:toolbutton
                  height: 20
                  background: Rectangle
                  {
                      color :  "cyan"
                  }
                  icon.source: "https://img.icons8.com/fluent/48/000000/menu--v2.png"
                  onClicked:
                  {
                      drawer.visible=true
                  }
              }
              Label
              {
                  id:titlelabel
                  text: "Home"
                  Layout.fillWidth: true
                  elide: Label.ElideRight

              }
          }
      }

      Drawer
         {
             id: drawer
             width: rootWindow.width/3
             height: rootWindow.height

          Column
          {
              anchors.fill: parent
              spacing: 4
              ToolButton
              {
                  height: toolbutton.implicitHeight
                  width: parent.width
                  background: Rectangle
                  {
                      color :  "cyan"
                  }
                  text: "One"
              }

              ToolButton
              {
                  height: toolbutton.implicitHeight
                  width: parent.width
                  background: Rectangle
                  {
                      color :  "cyan"
                  }
                  text: "Two"
              }
              ToolButton
              {
                  height: toolbutton.implicitHeight
                  width: parent.width
                  background: Rectangle
                  {
                      color :  "cyan"
                  }
                  text: "Three"
              }
         }
    }
}


*/


/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Spin Box demo"

    SpinBox
    {  id:spinbox
        anchors.centerIn: parent
        height: implicitHeight
        width: implicitWidth
        from: 1
        to:1000
        stepSize: 1
        focus: true
        editable: true
        onFocusChanged:
        {
            console.log("focus changed "+value)
        }
       onValueChanged:
        {
            console.log("on value changed "+value)
        }
    }
    Button
    {
        anchors.top:spinbox.bottom
        id:buttonid
        width: spinbox.width
        height: spinbox.height
        anchors.right: spinbox.right
        text:"Click me"
        onClicked:
        {
            buttonid.focus=true
        }
    }

}


*/

/*
ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Appplication Window and Menu Bar "

     menuBar: MenuBar {
            Menu { MenuItem {} }
            Menu { MenuItem {} }
        }
    header: ToolBar
    {

    }
   footer: TabBar
   {

   }

}

*/


/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "List View and List Model"

    ListView
    {
        id:listview1
        anchors.fill:parent
        delegate: delegateidd //Text {
           //text: name +" : "+ number
       // }

        model: ListModel
        {
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
            ListElement {  name: "Bill Smith"; number: "125264";}
            ListElement {  name: "Ramesh Kumar"; number: "5473264";}
            ListElement {  name: "Dinesh Choudhary"; number: "4175264";}
        }
    }

    Component  // custom Component for delegates
    { id:delegateid;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "blue"
             border.color: "yellow"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text: name +" : "+ number
             }
         }
    }

    Component
    {
        id: delegateidd
        Rectangle
         {
             id:rectid1
             width: rootWindow.width
             height: textid1.implicitHeight
             color: "blue"
             border.color: "yellow"
             radius: 8
             Text {
                 id: textid1
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text: name +" : "+ number
             }
         }
    }
}

*/


/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "List View and inline Model"

    ListView
    {
        id:listview1
        anchors.fill:parent
        delegate: delegateid
        model: ["jan" ,"jan" ,"jan" ,"jan" ,"jan" ,"jan" ,"jan" ,"final"]
    }


    Component  // custom Component for delegates
    { id:delegateid;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "blue"
             border.color: "yellow"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text:modelData
             }
         }
    }
}


*/

/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Header footer and highlight"

    ListView
    {
        id:listview1
        anchors.fill:parent
        delegate: delegateid
        model: ["jan" ,"feb" ,"march" ,"april" ,"may" ,"june" ,"july" ,"august","september","october","november","december"]
         header: headerid
         footer: footerid
         highlight: highlight
    }


    Component  // custom Component for delegates
    { id:delegateid;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "lightgreen"
             border.color: "yellow"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text:modelData
             }
             MouseArea
             {
                 anchors.fill: parent
                 onClicked:
                 {
                     listview1.currentIndex=index
                 }
             }
         }
    }

    Component  // custom Component for delegates
    { id:headerid;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "red"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text:"Header"
             }
         }
    }

    Component  // custom Component for delegates
    { id:footerid;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "red"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text:"Footer"
             }
         }
    }
    Component  // custom Component for delegates
    { id:highlight;
        Rectangle
         {
             width: parent.width
             color: "green"
             radius: 8
             z:3
             opacity: 0.3
         }
    }
}

*/

/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Section Decorations"

    ListView
    {
        id:listview1
        anchors.fill:parent
        delegate: delegateid
        section{
            property: "location"
            criteria: ViewSection.FullString
            delegate:delegateid2
        }

        model: ListModel
        {
            ListElement {  name: "Armaan"; location: "delhi";}
            ListElement {  name: "kamlesh"; location: "delhi";}
            ListElement {  name: "suraj"; location: "delhi";}
            ListElement {  name: "Nitin"; location: "delhi";}
            ListElement {  name: "coloumb"; location: "delhi";}
            ListElement {  name: "newton"; location: "delhi";}
            ListElement {  name: "ajmal"; location: "delhi";}
            ListElement {  name: "screen"; location: "delhi";}
            ListElement {  name: "flash"; location: "delhi";}
            ListElement {  name: "aktar"; location: "delhi";}
            ListElement {  name: "phasa"; location: "delhi";}
            ListElement {  name: "uuuu"; location: "mumbai";}
            ListElement {  name: "kkkk"; location: "mumbai";}
            ListElement {  name: "sdsa"; location: "mumbai";}
            ListElement {  name: "sdas"; location: "mumbai";}
            ListElement {  name: "fdf"; location: "mumbai";}
            ListElement {  name: "oooo"; location: "mumbai";}
            ListElement {  name: "vvv vggg"; location: "mumbai";}
            ListElement {  name: "ffrr  ff"; location: "mumbai";}
            ListElement {  name: "gfgfd"; location: "mumbai";}
            ListElement {  name: "ggg"; location: "mumbai";}
            ListElement {  name: "hhh"; location: "mumbai";}
            ListElement {  name: "hhhhrr"; location: "nerul";}
            ListElement {  name: "yyy"; location: "nerul";}
            ListElement {  name: "fsdfds"; location: "nerul";}
            ListElement {  name: "fdsfsdf"; location: "nerul";}
            ListElement {  name: "fffff"; location: "nerul";}
            ListElement {  name: "gggg"; location: "nerul";}
            ListElement {  name: "iiii"; location: "nerul";}
            ListElement {  name: "mmmm"; location: "nerul";}
            ListElement {  name: "pppp"; location: "nerul";}
        }
    }

    Component  // custom Component for delegates
    { id:delegateid;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "blue"
             border.color: "yellow"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text: name +" : "+ location
             }
         }
    }

    Component  // custom Component for delegates
    { id:delegateid2;
        Rectangle
         {
             id:rectid
             width: rootWindow.width
             height: textid.implicitHeight
             color: "cyan"
             radius: 8
             Text {
                 id: textid
                 width: implicitWidth
                 height: implicitHeight
                 anchors.centerIn: parent
                 font.pointSize:15
                 text: section
             }
         }
    }
}

*/

/*
ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Repeaters"

    Flow { anchors.fill: parent
        Repeater {
            model: 358
            Rectangle {
                width: 100; height: 40
                border.width: 1
                color: "yellow"
            }
        }
    }
}

*/

/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "Dynamic model"

 Dialog {
        id: inputDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: Overlay.overlay
        width:implicitWidth+40
        focus: true
        modal: true
        title: "Input"
        standardButtons: Dialog.Ok | Dialog.Cancel

        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            TextField {
                id:name
                focus: true
                placeholderText: "Name"
                Layout.fillWidth: true
            }
            TextField {
                id:location
                placeholderText: "Location"
                Layout.fillWidth: true
            }
        }
        onAccepted:
        {
            if(name.text!=="" && location.text!=="")
            {
                listmodels.append({  name: name.text,number:location.text})
                name.text="";  location.text=""
            }
            else
            {
                name.text="";  location.text=""
            }
     }
 }

 */


/*

ApplicationWindow
{
    id : rootWindow
    visible :true
    height: 600
    width : 400
    title: "XML list model"

  XmlListModel
  {
      id:xmllistmodel
      source: "qrc:/xml/xml files/xmldemo.xml"
    //  query : "//dependency[2]"
     query: "/dependencies/dependency"
      XmlRole
      {
          name:"groupId"
          query: "groupId/string()"
      }
      XmlRole
      {
          name:"artifactId"
          query: "artifactId/string()"
      }
      XmlRole
      {
          name:"version"
          query: "version/number()"
      }
      XmlRole
      {
          name:"scope"
          query: "scope/string()"
      }
  }

  ListView
  {
      id:listviewid
      anchors.fill: parent
      model:xmllistmodel
      spacing: 10
      delegate: Rectangle
      {
          color:"blue"
          width:parent.width
          height:30
          radius:15
          Text {
              anchors.centerIn: parent
              id: textid
              font.pointSize: 10
              text: groupId+","+artifactId+","+version+","+scope
          }
      }
  }
}

*/

