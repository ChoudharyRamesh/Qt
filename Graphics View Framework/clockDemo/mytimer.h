#ifndef MYTIMER_H
#define MYTIMER_H

#include <QWidget>
#include<QElapsedTimer>
#include<QTime>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MyTimer; }
QT_END_NAMESPACE

class MyTimer : public QWidget
{
    Q_OBJECT

public:
    MyTimer(qint64 milisec=0,QWidget * parent=nullptr);
    void start();
    void restart(qint64 milisec=0);
    void pause();
    void resume();
    QTime elaspedTime();
    ~MyTimer();

private:
    qint64 milisec;
    QElapsedTimer elapsedTimer;
    bool isPaused;
    QTime clock;
     QTimer * timer ;
    Ui::MyTimer *ui;
};
#endif // MYTIMER_H
