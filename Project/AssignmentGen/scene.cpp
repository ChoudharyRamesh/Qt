#include "scene.h"

Scene::Scene(bool *isPenEditingEnabled, int *penWidth, bool *isPen, QRectF * maxSceneRect,QObject *parent): QGraphicsScene(parent)
{

    //while text editing in scene
    QObject::connect(this,&Scene::changed,[this](){
        if(itemsBoundingRect().height()>this->maxSceneRect->height())
            setSceneRect(*this->maxSceneRect);
    });

    this->isPenEditingEnabled=isPenEditingEnabled;
    this->penWidth=penWidth;
    this->isPen=isPen;
    this->maxSceneRect=maxSceneRect;

    pen.setColor(QColor(22,38,76,230));
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
    //pen.setCosmetic(true);


}


void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    QPointF mpos = event->scenePos();
    if(mpos.x()<=0  ||   mpos.y()<=0  ||
            mpos.x()>=maxSceneRect->width() ||
            mpos.y()>=maxSceneRect->height())
    {  //remove outer items
        setSceneRect(*maxSceneRect);
        auto insideItems =  items(*maxSceneRect,Qt::ItemSelectionMode::IntersectsItemBoundingRect);
        auto allItems = items();
        for(auto item : insideItems)
            allItems.removeAt(allItems.indexOf(item));
        qDeleteAll(allItems);
        return;
    }

    if(!(*isPenEditingEnabled) || !drawing)
        return  QGraphicsScene::mouseMoveEvent(event);
    pen.setWidth(*penWidth);
    adjustment = (*penWidth)+5;

    QPointF  newPoint = event->scenePos();

    if(*isPen)
    {
        QPointF center1 = QLineF(lastPoint,newPoint).center();
        QPointF center2 = QLineF(lastPoint,center1).center();
        QPointF center3 = QLineF(center1,newPoint).center();
        addItem(new Line(lastPoint,center2,pen));
        addItem(new Line(center2,center1,pen));
        addItem(new Line(center1,center3,pen));
        addItem(new Line(center3,newPoint,pen));
    }
    else
    {
        QList< QGraphicsItem *> itemlist = items(newPoint.x(),newPoint.y(),50*(*penWidth),
                                                 50*(*penWidth), Qt::ContainsItemShape,
                                                 Qt::SortOrder::AscendingOrder);
        Line * item = nullptr;
        for(int i=0;i<itemlist.size();i++)
        {
            item =   dynamic_cast<Line *>(itemlist.at(i));
            if(item!=nullptr)
                removeItem(item);
        }
    }

    update(QRectF(lastPoint,newPoint).normalized()
           .adjusted(-adjustment, -adjustment, +adjustment, +adjustment));
    lastPoint = newPoint;
    QGraphicsScene::mouseMoveEvent(event);

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastPoint = event->scenePos();
    drawing=true;
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    drawing=false;
    QGraphicsScene::mouseReleaseEvent(event);
}



