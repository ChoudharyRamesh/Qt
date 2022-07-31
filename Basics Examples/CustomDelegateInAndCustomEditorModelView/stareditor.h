
#ifndef Star_H
#define Star_H

#include<QWidget>
#include<QDebug>
#include <QPainter>
#include <QMouseEvent>
#include<QPen>
#include<QBrush>
#include<QPolygon>


class StarEditor : public QWidget
{
    Q_OBJECT

public:
    explicit StarEditor(QWidget *parent = nullptr);
    ~StarEditor();
    int getStarRating() const;
    void setStarRating(int value);

signals:
    void editingFinished();

public slots:

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


private:
    int rating=0;
    QPolygon poly;
    int h,r,transform,w,tempWidth;
};
#endif // Star_H
