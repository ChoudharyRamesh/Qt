#ifndef Indicator_H
#define Indicator_H

#include <QWidget>
#include<QPainter>
#include<QPen>
#include<QDebug>
#include<QBrush>
#include<QTimer>

class Indicator : public QWidget
{
    Q_OBJECT

public:
    Indicator(QWidget *parent = nullptr);
    ~Indicator();

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    QSize sizeHint() const override;

public slots:
   void activateNormal(); // green
   void activateWarning(); //yellow
   void activateDanger();  // red

private:
    bool redActive;
    bool greenActive;
    bool yellowActive;
    bool lightsOn;
    void toggleLights();
    QTimer * timer;
    QPainter * painter;
    QPen mpen;
};
#endif // Indicator_H
