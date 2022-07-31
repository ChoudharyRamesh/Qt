#ifndef CUSTOM_PUSH_BUTTON
#define CUSTOM_PUSH_BUTTON

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QMouseEvent>

class CustomPushButton : public QPushButton
{
    Q_OBJECT

public:
    CustomPushButton(QWidget *parent = nullptr);
    ~CustomPushButton();

signals:
     void onDoubleClicked();

protected:
     void mouseDoubleClickEvent(QMouseEvent *event) override;
};
#endif // CUSTOM_PUSH_BUTTON
