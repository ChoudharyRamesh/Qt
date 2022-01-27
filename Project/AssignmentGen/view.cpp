#include "view.h"
#include<scene.h>
#include<QTextDocument>

View::View(QWidget *parent)
    : QGraphicsView(parent){
    //remove view border line
    setFrameStyle(0);
}
