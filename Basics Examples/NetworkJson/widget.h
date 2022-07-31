#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QNetworkAccessManager>
#include<QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void dataReadyToRead();
    void dataReadFinished();
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager * netmanager;
    QNetworkReply * netreply;
    QByteArray bytearray;
};
#endif // WIDGET_H
