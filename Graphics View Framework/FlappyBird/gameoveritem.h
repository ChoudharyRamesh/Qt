#ifndef GAMEOVERITEM_H
#define GAMEOVERITEM_H

#include<QGraphicsProxyWidget>
#include<QPushButton>
#include<QApplication>
#include<QTime>
#include<QLabel>

class GameOverItem:public QGraphicsProxyWidget
{
public:
    GameOverItem(QTime elapsedTime);
   ~GameOverItem();
    QPushButton * restart;
    QPushButton * exit;
private:
    QLabel * baselabel;
    QLabel * pixlabel;
    QLabel * textlabel;
    QLabel * bestScoreLabel;
    QString highScore;

};

#endif // GAMEOVERITEM_H
