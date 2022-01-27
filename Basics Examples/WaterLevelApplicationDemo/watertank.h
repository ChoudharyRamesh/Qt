#ifndef WATERTANK_H
#define WATERTANK_H

#include <QWidget>
#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QDebug>
#include<QTimer>
#include<QMediaPlayer>
#include<QUrl>

class WaterTank : public QWidget
{
    Q_OBJECT
public:
    explicit WaterTank(QWidget *parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int waterHeight;
    QTimer * timer;
    QMediaPlayer player;
    QVideoWidget * videoWidget;
private slots:
   void playWarningAlert();
   void playDangerAlert();
 signals:
    void normal();  // green
    void warning(); //yellow
    void danger(); //red
};

#endif // WATERTANK_H
