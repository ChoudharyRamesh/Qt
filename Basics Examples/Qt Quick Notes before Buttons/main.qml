import QtQuick 2.15
import QtQuick.Window 2.15
import "utility.js" as Methods   // first letter should be capital
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window
{
   id : rootWindow
   visible :true
   height: 800
   width : 800
   title: "Qt Quick Control"

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







/*
Qt global object
              for(var i=0;i<fonts.length;i++)
               {
                 console.log(i+" "+fonts[i])
             }

              var mname = "Daniel Gakwaya"
              var hashname = Qt.md5(mname)
               console.log(hashname)
               // open url
              Qt.openUrlExternally("https://www.facebook.com")

                 //open local file manager
                  //Qt.openUrlExternally("file:///C:/Users/Nishant Choudhary/Pictures/Camera Roll/WIN_20190212_00_10_33_Pro.jpg")

                 // find current runnning platform
                  // console.log(Qt.platform.os)
 */


/*
  property and signal handler demo

Window {
   id : rootWindow
   visible :true
   height: 600
   width: 600
   title: "property and signal handler demo"

   property string first_name: "Ramesh"
   onFirst_nameChanged:
   {
       console.log("first name is changed to "+first_name)
   }

   Rectangle
   {
       width:300
       height:100
       color: "greenyellow"
       anchors.centerIn: parent
       MouseArea
       {
           anchors.fill:parent
           onClicked:
           {
               first_name = "kumar"
           }
       }
   }

   Component.onCompleted:
   {
       console.log("the first name is "+first_name)
   }

}

*/


/* item element

Window {
   id : rootWindow
   visible :true
   height: 600
   width: 600
   title: "Items elemets"

   Item {
       id: contianerItemId
       x:50; y:50;
       width:400
       height: 300

       Rectangle
       {
           anchors.fill: parent
           color: "beige"
           border.color: "black"
       }


       Rectangle
       {   x:0;y:10;
           width: 50
           height: 50
           //anchors.centerIn: parent
           color: "red"
           MouseArea
           {
               anchors.fill:parent
               onClicked:
               {

               }
           }
       }

       Rectangle
       {  x:60;y:10;
           width: 50
           height: 50
           //anchors.centerIn: parent
           color: "green"
           MouseArea
           {
               anchors
               {
                   fill:parent
               }
               onClicked:
               {

               }
           }
       }
       Rectangle
       {  x:120;y:10;
           width: 50
           height: 50
           //anchors.centerIn: parent
           color: "blue"
           MouseArea
           {
               anchors.fill:parent
               onClicked:
               {

               }
           }
       }
       Rectangle
       {  x:180;y:10;
           width: 50
           height: 50
           //anchors.centerIn: parent
           color: "magenta"
           MouseArea
           {
               anchors.fill:parent
               onClicked:
               {

               }
           }
       }

   }
}

*/

/*
image element
Window {
   id : rootWindow
   visible :true
   height: 600
   width: 600
   title: "Image elemets"

   Image {
       id: imageid
       anchors.centerIn: parent
       //local source
       //source: "file:///C:/Users/Nishant Choudhary/Pictures/Camera Roll/IMG_20181116_212714 (2).jpg"
       //html source
       /*source: "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.\
                    com/images/dog-puppy-on-garden-royalty-free-image-\
                    1586966191.jpg?crop=1.00xw:0.669xh;0,0.190xh&resize=980:*"
   }

}
*/

/*
 Custom Component Demo and Row ,column ,private properties"

Window {
   id : rootWindow
   visible :true
   height: 600
   width: 600
   title: "Custom Component Demo and Row ,column ,private properties"

//   Row  // or column // or grid
//   {
//       Rectangle
//       {
//           width: 300
//           height: 100
//           color: "red"
//       }
//       Rectangle
//       {
//           width: 300
//           height: 100
//           color: "blue"
//       }
//   }

      Row
      {
          CustomButton{}
          CustomButton{}
          CustomButton{}
      }
}

*/


/* signal and slots
Window {
   id : rootWindow
   visible :true
   height: 600
   width: 600
   title: "Signal and slots"

   property string buttonName1: "default"
   property string buttonName2: "default"

  Row{
   Rectangle
   {
       id:rectid1
       signal greet(string message)
       width:100
       height: 30
       radius: 30
       color: "blue"
       Text {
           id: rectid1text
           text: buttonName1
           anchors.centerIn: parent
       }
   }

   Rectangle
   {
       id:rectid2
       width:100
       height: 30
       radius: 30
       function myslot(mymessage)
       {
           buttonName2 = buttonName1
           buttonName1 =mymessage
       }
       color: "pink"
       Text {
           id: rectid2text
           text: buttonName2
           anchors.centerIn: parent
       }
   }

   Rectangle
   {  property  string customcolor: "darkcyan"
       id:rectid3
       width:100
       height: 30
       radius: 30
       color: customcolor
       Text {
           id: rectid3text
           text: "Click me"
           anchors.centerIn: parent
       }
       MouseArea
       {
           anchors.fill: parent
           onPressed:
           {
               rectid3.customcolor = "cyan"
           }
           onReleased:
           {
               rectid1.greet(textEdit1.text);
                rectid3.customcolor = "darkcyan"
           }
       }
   }

   Rectangle
   {
       id:rectid4
       width:100
       height: 30
       color: "yellow"
       TextEdit
       {
           id:textEdit1
           anchors.fill: parent
           color: "black"
           textMargin: 5
       }
   }
  }



   Component.onCompleted:
   {
       rectid1.greet.connect(rectid2.myslot)
   }

}
*/


/* User input ,rich text, change focus

Window {
   id : rootWindow
   visible :true
   height: 600
   width: 600
   title: "User input"

Column
{
   Rectangle
       {
           id:firstname
           color: "beige"
           width: 600
           focus: true
           height: 300
           Flickable
            {
                 anchors.fill: parent
                contentHeight: firstnameedit.implicitHeight
                clip: true
                TextEdit
                {
                    id: firstnameedit
                    anchors.fill: parent
                    selectionColor: "blue"
                    selectByMouse: true
                    HtmlText{ id:htmltext }
                    text : "okk" //htmltext.htmlvalue
                    wrapMode: TextEdit.Wrap
                    onEditingFinished:
                    {
                        console.log(firstnameedit.text)
                    }
                 }
            }
      }
   Rectangle
       {
           id:rectangle
           color: "red"
           width: 600
           height: 300
           MouseArea
           {
               anchors.fill: parent
               onClicked:
               {
                   rectangle.focus = true
               }
           }
       }
}
}

*/


/*
Window {
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Drag and Drop Mouse Event"

   Rectangle
   {
       width: parent.width
       height: 200
       color: "beige"
       Rectangle
       {
           id:dragablerect
           width: 50
           height: 50
           color: "red"
        }
       MouseArea
       {
           id:mouseArea
           anchors.fill: parent
           drag.target:dragablerect
           drag.axis: Drag.XAndYAxis
           drag.minimumX: 0
           drag.minimumY: 0
           drag.maximumX: width-dragablerect.width
           drag.maximumY: height-dragablerect.height
       }

    }

}
*/

/*
Window {
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Key Event"

   Rectangle
   {
       width: parent.width
       height: 200
       focus: true
       color: "blue"
       Keys.onPressed:
       {
           console.log(event.key)
       }
   }
}

*/


/*
Window {
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Key Navigation demo"

   Row
   {
       anchors.centerIn: parent
       Rectangle
       {  id:rect1
           width: 100
           height: width
           radius: 100
           border.color: "black"
           color: "green"
           focus: true
           Keys.onPressed:
           {
               console.log("i am rect 1")
           }
           onFocusChanged:
           {
               if(rect1.focus==true)
               {
                   rect1.border.width =5
                   rect1.border.color ="cyan"
               }
               else
               {
                   rect1.border.width =1
                   rect1.border.color ="black"
               }
           }
           KeyNavigation.tab: rect2
       }

       Rectangle
       {  id:rect2
           width: 100
           height: width
           radius: 100
           border.color: "black"
           color: "green"
           Keys.onPressed:
           {
               console.log("i am rect 2")
           }
           onFocusChanged:
           {
               if(rect2.focus==true)
               {
                   rect2.border.width =5
                   rect2.border.color ="cyan"
               }
               else
               {
                   rect2.border.width =1
                   rect2.border.color ="black"
               }
           }
          KeyNavigation.tab: rect1
       }
   }
}

*/


/*
Window {
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Focus Scope Demo"

   Column
   {
       MButton
       {
       }
       MButton
       {
           focus: true
           color: "green"
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
   title: "calling javarscript object or function from external js file"
   Rectangle
   {
       id:rectid
       width: 200
       height: 100
       color: "red"
       MouseArea
       {
           anchors.fill:parent
           onClicked:
           {
               Methods.func();
              console.log(Methods.func2(5,8));

               // or indirect calling
             console.log(Methods.temp(5,8));

               //Qt import callling
              Methods.fun4()
           }
       }
   }
}

*/


/*
Window
{
// anchoring can be done between siblings or parent and child only *****
   id : rootWindow
   visible :true
   height: 600
   width : 600
   title: "Anchros Lines ,Positioning, Margin and Offset in Qml"
   // margin ka effect tabhi dikheg jab woh object kisi dusre object se outside anchros lines k though
   // connected hoga kyoki margin object ki outer anchor line ko move karta hai.

   //margin
   Rectangle
   {
       height: 100
       width : 100
       color: "red"
       id: rect1;
       anchors.margins:10; // no effect bcz eiski anchors eiski positioning anchor lines se nhi ki gai hai.
   }
   Rectangle
    {
       id: rect2;
       height: 100
       width : 100
       color: "green"
       anchors.left: rect1.right;
       anchors.leftMargin: 5; // working bcz left line is conneted to rect1
       anchors.rightMargin: 5  // no effect bcz no connection
    }

   //offset
   // offset ka effect tabhi dikheg jab woh object kisi dusre object se center anchros lines k though
   // connected hoga kyoki offset object ki center anchor line ko move karta hai.
   Rectangle
   {
       height: 100
       width : 100
       x:0
       y:100
       color: "yellow"
       id: rect3;
       anchors.baselineOffset: 10;
   }
   Rectangle
    {
       id: rect4;
       height: 100
       width : 100
       y:100
       color: "purple"
       anchors.horizontalCenter: rect3.right;
       anchors.horizontalCenterOffset: width/2; // this is offset
    }

    // anchors.centerIn:parent
        // is equal to
    //anchors.verticalCenter: parent.verticalCenter
    //anchors.horizontalCenter:parent.horizontalCenter

}

*/


/*
Window
{
   id : rootWindow
   visible :true
   height: mgrid.implicitWidth
   width : mgrid.implicitHeight
   title: "Layout Demo"

  GridLayout  // or RowLayout //or Columnlayout
  {
      id:mgrid
      columns: 2
      rows:5
      anchors.fill: parent
      anchors.margins:5
      CustomButton{Layout.fillHeight: true; Layout.fillWidth: true} CustomButton{Layout.fillHeight: true; Layout.fillWidth: true}
      CustomButton{Layout.fillHeight: true; Layout.fillWidth: true} CustomButton{Layout.fillHeight: true; Layout.fillWidth: true}
      CustomButton{Layout.fillHeight: true; Layout.fillWidth: true} CustomButton{Layout.fillHeight: true; Layout.fillWidth: true}
      CustomButton{Layout.fillHeight: true; Layout.fillWidth: true} CustomButton{Layout.fillHeight: true; Layout.fillWidth: true}
      CustomButton{Layout.fillHeight: true; Layout.fillWidth: true} CustomButton{Layout.fillHeight: true; Layout.fillWidth: true}
  }

}

*/

/*
Window
{
   id : rootWindow
   visible :true
   height: 800
   width : 800
   title: "Flow Layout Demo"
   Flow
   {
       id:mgrid
       anchors.fill: parent
       anchors.margins:5
       spacing: 1

     //  flow:Flow.TopToBottom
       flow:Flow.LeftToRight

   // layoutDirection:"LeftToRight"
       layoutDirection: "RightToLeft"

        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
        CustomButton{} CustomButton{}CustomButton{} CustomButton{}
    }

}

*/





