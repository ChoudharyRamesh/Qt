#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QThreadPool>
#include<QEvent>
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    bool event(QEvent *event) override;
    ~Widget();

private slots:
    void on_startWorkButton_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
