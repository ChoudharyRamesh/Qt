#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QThread>
#include "consumer.h"
#include "producer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_sendData_clicked();
public slots:
    void recieveDataFromConsumerThread(const QString & data);

private:
    Ui::Widget *ui;
    QThread * cthread;
    QThread * pthread;
    Consumer * consumer;
    Producer * producer;
signals:
    void sendDataToProducerThread(const QString & data);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // WIDGET_H
