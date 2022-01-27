#ifndef QGRAPHICSCUSTOMTEXTITEM_H
#define QGRAPHICSCUSTOMTEXTITEM_H

#include <QObject>
#include<QGraphicsTextItem>
#include<QKeyEvent>
#include<QApplication>
#include<QClipboard>
#include<QTextDocument>
#include<QRandomGenerator>

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextItem(int maxboundingRectHeight=INFINITY,bool * randomWordSpacing=nullptr,QGraphicsItem *parent = nullptr);
private:
    int maxboundingRectHeight=INFINITY;
    bool *randomWordSpacing;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // QGRAPHICSCUSTOMTEXTITEM_H
