#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QtConcurrent>
#include<QLabel>
#include "singlethreadedwork.h"
#include "multithreadedwork.h"
#include<QMovie>
#include<QElapsedTimer>

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
    void on_chooseFolder_single_clicked();
    void on_chooseFolder_multi_clicked();

private:
    Ui::Widget *ui;
    QMovie *movie;
    QThread * singlethread;
    SingleThreadedWork * singleworker;
    QThread * multithread;
    MultiThreadedWork * multiworker;
    bool isworkFinished_single;
    bool isworkFinished_multi;
};
#endif // WIDGET_H
