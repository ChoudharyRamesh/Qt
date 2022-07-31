#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include<QTcpServer>
#include<QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void gotNewConnection();
    void readData();
    void disconnected();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTcpServer * server;
    QTcpSocket * socket;
    QProcess  process;
};
#endif // WIDGET_H
