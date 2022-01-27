#ifndef WIDGET_H
#define WIDGET_H

#include<QObject>
#include <QWidget>
#include"mthread.h"

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
    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_resumeButon_clicked();

private:
    Ui::Widget *ui;
    MThread * mthread;
};
#endif // WIDGET_H
