#include "view.h"
View::~View(){}

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    setScene(&scene);
    scene.setBackgroundBrush(QBrush(backgroundColor));

    // node and corresponding edge colors
    colors.append("red");
    colors.append("green");
    colors.append("blue");
    colors.append("yellow");
    colors.append("purple");
    colors.append("orange");
    colors.append(QColor("#00ff7f"));
    colors.append(QColor("#007fff"));
    colors.append(QColor("#96111e"));
    colors.append(QColor("#c71585"));
    colors.append(QColor("#800000"));
    colors.append(QColor("#f032e6"));
    colors.append(QColor("#e6194B"));
    colors.append(QColor("#aaffc3"));
    // need 50 different color(human noticable) except white

    //test
    QList<QList<int>> testMat=
    {{0,1,1,1,1,1,0,0,0,0,0},
     {1,0,1,0,0,1,0,0,1,0,0},
     {1,1,0,1,0,0,0,1,0,0,0},
     {1,0,1,0,1,0,1,0,0,0,0},
     {1,0,0,1,0,1,0,0,0,1,0},
     {1,1,0,0,1,0,0,0,0,0,1},
     {0,0,0,1,0,0,0,0,0,1,0},
     {0,0,1,0,0,0,1,0,0,0,0},
     {0,1,0,0,0,0,0,1,0,0,0},
     {0,0,0,0,1,0,0,0,0,0,1},
     {0,0,0,0,0,1,0,0,1,0,0}};

    plotAdjacencyMatrix(testMat);
}


void View::plotAdjacencyMatrix(QList<QList<int> > matrix)
{
    scene.clear();

    //create graph
    AMGraph graph(matrix);
    QList<QList<int>> sortedNodes = graph.getSortedNodes();

    //generate Node coordinate
    QMap<int,QGraphicsNodeItem *> points; // index,point
    int boundry=0;
    for(int i=0;i<sortedNodes.size();i++)
    {
        int samePriorityNodesSize = sortedNodes.at(i).size();
        if(i==0)
        {
            if(samePriorityNodesSize==1)
            {
                QGraphicsNodeItem *  node =new QGraphicsNodeItem(nodeRadius,sortedNodes.at(i).at(0)+1,QPointF(0,0));
                points.insert(sortedNodes.at(i).at(0),node);
                continue;
            }
        }

        boundry+=90;
        float radius = boundry*1.414;
        float angle = 360/samePriorityNodesSize;
        float currentAngle=0;
        float rand = QRandomGenerator::global()->bounded(0,150);
        for(int j=0;j<samePriorityNodesSize;j++)
        {
            float  x = radius*cos(qDegreesToRadians(currentAngle+rand));
            float  y = radius*sin(qDegreesToRadians(currentAngle+rand));

            QGraphicsNodeItem *  node =new QGraphicsNodeItem(nodeRadius,sortedNodes.at(i).at(j)+1,QPointF(x,y));
            points.insert(sortedNodes.at(i).at(j),node);
            currentAngle+=angle;
        }
    }

    //add lines ref to left and right node and put into scene
    QPen pen;
    pen.setWidth(linePenWidth);
    int colorCount=0;

    for(int y=0;y<matrix.size();y++)
    {
        pen.setColor(colors.at(colorCount));colorCount++;
        if(colorCount>colors.size())colorCount=0;

        for(int x=0;x<matrix.size();x++)
        {
            if(graph.hasEdge(y,x))
            {
                QGraphicsNodeItem * node1 = points.value(y);
                QGraphicsNodeItem * node2 = points.value(x);
                QLineF line(node1->getNodeCenter(),node2->getNodeCenter());

                //check if node1 has already this "line"
                QGraphicsLineItem * preAddedLine =  node1->checkConnectedLine(line);
                if(preAddedLine != nullptr)
                {
                    // If this line is pre added it means this edge is bidirectional
                    QPen pen = preAddedLine->pen();
                    pen.setColor(bidirectionalEdgeColor);
                    preAddedLine->setPen(pen);
                    continue;
                }

                //check if node2 has already this "line"
                QGraphicsLineItem * preAddedLine_ =  node1->checkConnectedLine(line);
                if(preAddedLine_ != nullptr)
                {
                    QPen pen = preAddedLine_->pen();
                    pen.setColor(bidirectionalEdgeColor);
                    preAddedLine_->setPen(pen);
                    continue;
                }

                auto lineItem = scene.addLine(line,pen);
                node1->addLine(lineItem,1);
                node2->addLine(lineItem,2);
            }
        }
    }

    //add nodes into scene
    colorCount=0;
    pen.setWidth(nodePenWidth);
    for(auto node:points.values())
    {
        pen.setColor(colors.at(colorCount));colorCount++;
        if(colorCount>>colors.size())colorCount=0;
        node->setPen(pen);
        node->setBrush(QBrush(nodeBrushColor));
        scene.addItem(node);
    }
}


void View::mouseMoveEvent(QMouseEvent *event)
{ 
    if(isMousPressed && event->modifiers()==Qt::KeyboardModifier::ControlModifier)
    {
        QPointF newPoint =  event->pos();
        QPointF dif =  lastpoint - newPoint;
        if(transform().m11()<1)
            dif =  QPointF(dif.x()/transform().m11(),dif.y()/transform().m22());
        QRectF sR = sceneRect();
        setSceneRect(sR.x()+dif.x(),sR.y()+dif.y(),sR.width(),sR.height());
        lastpoint = newPoint;
    }
    else QGraphicsView::mouseMoveEvent(event);
}

void View::mousePressEvent(QMouseEvent *event)
{
    isMousPressed=true;
    lastpoint =  event->pos();
    QGraphicsView::mousePressEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    isMousPressed=false;
    QGraphicsView::mouseReleaseEvent(event);
}


void View::scalingTime(qreal q) {
    Q_UNUSED(q);
    qreal factor = 1.0+ qreal(_numScheduledScalings)/300.0;
    scale(factor,factor);
}

void View::animFinished() {

    if (_numScheduledScalings > 0)  _numScheduledScalings--;
    else  _numScheduledScalings++;
    sender()->~QObject();
}

void View::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers()==Qt::KeyboardModifier::ControlModifier)
    {
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15; // see QWheelEvent documentation
        _numScheduledScalings += numSteps;
        if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
            _numScheduledScalings = numSteps;
        QTimeLine *anim = new QTimeLine(350, this);
        anim->setUpdateInterval(20);
        connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
        connect(anim, SIGNAL (finished()), SLOT (animFinished()));
        anim->start();
    }
    QGraphicsView::wheelEvent(event);
}

