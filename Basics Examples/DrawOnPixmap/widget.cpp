#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    int ps = (5*(100));
    QPixmap pixmap(ps,ps+(ps/3)); // (3:4)
    pixmap.fill(Qt::white);
    QPen pen("#00cd00");
    QBrush brush("#00cd00");
    QPainter painter(&pixmap);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(0,0,pixmap.width(),pixmap.height());

    // set upper rectangle
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.drawRect(0,0,pixmap.width(),pixmap.height()/4);

    //draw font ( learn )
    QFont font("Consolas",(pixmap.width()/7),QFont::Bold);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(0,0,pixmap.width(),pixmap.height()/4,Qt::AlignHCenter | Qt::AlignVCenter,"Learn");


    font.setPointSize(pixmap.height()/2);
    font.setFamily("Bahnschrift Light SemiCondensed");
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(0,pixmap.height()/4-pixmap.height()/40,pixmap.width(),pixmap.height()-pixmap.height()/4,Qt::AlignHCenter | Qt::AlignVCenter,"Qt");
    ui->label->setPixmap(pixmap);

     // save pixmap
    QFile fptr;
    fptr.setFileName("E:/pic3.png");
    fptr.open(QFile::WriteOnly);
    pixmap.save(&fptr, "PNG");

}

Widget::~Widget()
{
    delete ui;
}

