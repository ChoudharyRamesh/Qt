#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include<QSize>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("QSettingDemo");
    setWindowOpacity(0.3);

    //load setting
    QSettings setting("mycompany","QSettingDemo");
    setting.beginGroup("MainWidget");
    ui->textEdit->setText(setting.value("textEditText").toString());
    setGeometry(setting.value("geometry").toRect());
    setting.endGroup();
}

Widget::~Widget()
{
    //save setting
    QSettings setting("mycompany","QSettingDemo");
    setting.beginGroup("MainWidget");
    setting.setValue("title",size());
    setting.setValue("textEditText",ui->textEdit->toHtml());
    setting.setValue("geometry",geometry());
    setting.endGroup();
    delete ui;
}

