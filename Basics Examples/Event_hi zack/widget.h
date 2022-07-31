#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QCoreApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
     Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    bool event(QEvent *event) override;
private:
    Ui::Widget *ui;


};
#endif // WIDGET_H
