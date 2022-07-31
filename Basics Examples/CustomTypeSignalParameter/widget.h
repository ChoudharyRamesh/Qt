#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QThread>
#include "worker.h"
#include "progressnumber.h"

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
    void on_startWorkButton_clicked();
    void updateProgress(ProgressNumber progressNumber); // custom type
    void updateProgressInt(int progress);

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
