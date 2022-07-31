#include "CustomPushButton.h"

CustomPushButton::CustomPushButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this,&CustomPushButton::onDoubleClicked,this,[=](){
        qDebug()<<"double clicked";
    });
}

CustomPushButton::~CustomPushButton()
{

}

void CustomPushButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
    emit onDoubleClicked();
}
