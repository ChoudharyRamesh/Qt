#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QThread>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void Dowork1(int a=0);
    void Dowork2();
    void threadOnGlobalFunction();
    void threadOnLambdaPtrFunction();
    void threadOnLambdaDirectFunction();
    void threadOnMemberFunction();
    void threadOnMemberFunctionAndShareResources();
    ~Widget();

private slots:
    void on_global_clicked();
    void on_lambda_clicked();
    void on_lambdaonfly_clicked();
    void on_onMember_clicked();
    void on_SharingResources_clicked();

private:
    Ui::Widget *ui;
    int isSharedData=10;
    QThread * secondaryThread;
};
#endif // WIDGET_H
