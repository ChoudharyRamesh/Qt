#include "textitem.h"
#include<QTextCursor>

TextItem::TextItem
(int maxboundingRectHeight,bool * randomWordSpacing,QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    this->maxboundingRectHeight=maxboundingRectHeight;
    this->randomWordSpacing=randomWordSpacing;
}

void TextItem::keyPressEvent(QKeyEvent *event)
{
    if(boundingRect().height()>maxboundingRectHeight)
    {
        if(event->modifiers()==Qt::ControlModifier  && event->key()==Qt::Key_A){
            return  QGraphicsTextItem::keyPressEvent(event);
        }
        QKeyEvent * kpe = new QKeyEvent (QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier);
        return  QGraphicsTextItem::keyPressEvent(kpe);
    }

    if(event->key()==Qt::Key_Space && randomWordSpacing!=nullptr)
    {
        if(*randomWordSpacing)
        {
            qsizetype random = QRandomGenerator::global()->bounded(1,3);
            QString space(random,' ');
            QKeyEvent * kpe = new QKeyEvent (QEvent::KeyPress,Qt::Key_Space,Qt::NoModifier,space);
            return  QGraphicsTextItem::keyPressEvent(kpe);
        }
    }

    if(event->modifiers()==Qt::ControlModifier  && event->key()==Qt::Key_V)
    {
        QClipboard *clipboard = QApplication::clipboard();
        QString original = clipboard->text();
        QString text = original;

        //randomize word spacing
        if(randomWordSpacing!=nullptr)
        if(*randomWordSpacing)
        {
            for(int i=0;i<text.size();i++)
            {
                if(text.at(i)==' ')
                    if(i+1<text.size() && text.at(i+1)!=' ')
                    {
                        qsizetype random = QRandomGenerator::global()->bounded(1,3);
                        if(random==2)
                        {text.insert(i,' '); i++; }
                    }
            }
        }

        clipboard->clear();
        clipboard->setText(text);
        QGraphicsTextItem::keyPressEvent(event);
        clipboard->clear();
        clipboard->setText(original);
        return;
    }
    else  return QGraphicsTextItem::keyPressEvent(event);
}
