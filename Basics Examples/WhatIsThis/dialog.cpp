#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
#include<QDesktopServices>
#include<QWhatsThisClickedEvent>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->pushButton->setWhatsThis("for more informaton <a href='www.google.com'>link</a>");
    installEventFilter(this);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::WhatsThisClicked)
    {  QWhatsThisClickedEvent * linkevent = static_cast<QWhatsThisClickedEvent *>(event);
        QDesktopServices::openUrl(QUrl(linkevent->href()));
        return  true;
    }
    else return QDialog::eventFilter(watched,event);
}
