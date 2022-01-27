#include "stardelegate.h"
#include "stareditor.h"
#include <QPainter>

StarDelegate::StarDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    poly << QPoint(0, 85) << QPoint(75, 75)
         << QPoint(100, 10) << QPoint(125, 75)
         << QPoint(200, 85) << QPoint(150, 125)
         << QPoint(160, 190) << QPoint(100, 150)
         << QPoint(40, 190) << QPoint(50, 125)
         << QPoint(0, 85);
}

void StarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() ==2){

        QRect rect = option.rect.adjusted(10,10,-10,-10);

        int starNumber = index.data().toInt();


        painter->save();

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::black));

        painter->translate(rect.x(),rect.y());

        painter->scale(0.1,0.1);

        for(int i = 0; i < starNumber ; i ++){
            painter->drawPolygon(poly);
            painter->translate(220,0);
        }

        painter->restore();

    }

//  if(index.column() ==2){
//    int w = (width()/5);
//    int h = height();
//    int r = w/2;
//    int ir = r*0.38196601125;  // ineer radius of star
//    QPoint a = QPoint(r*qCos(qDegreesToRadians(-18.0f)), r*qSin(qDegreesToRadians(-18.0f)));
//    QPoint b = QPoint(r*qCos(qDegreesToRadians(54.0f)), r*qSin(qDegreesToRadians(54.0f)));
//    QPoint c = QPoint(r*qCos(qDegreesToRadians(126.0f)), r*qSin(qDegreesToRadians(126.0f)));
//    QPoint d = QPoint(r*qCos(qDegreesToRadians(198.0f)), r*qSin(qDegreesToRadians(198.0f)));
//    QPoint e = QPoint(r*qCos(qDegreesToRadians(270.0f)), r*qSin(qDegreesToRadians(270.0f)));

//    QPoint ad = QPoint(ir*qCos(qDegreesToRadians(-54.0f)), ir*qSin(qDegreesToRadians(-54.0f)));
//    QPoint bd = QPoint(ir*qCos(qDegreesToRadians(18.0f)), ir*qSin(qDegreesToRadians(18.0f)));
//    QPoint cd = QPoint(ir*qCos(qDegreesToRadians(90.0f)), ir*qSin(qDegreesToRadians(90.0f)));
//    QPoint dd = QPoint(ir*qCos(qDegreesToRadians(162.0f)), ir*qSin(qDegreesToRadians(162.0f)));
//    QPoint ed = QPoint(ir*qCos(qDegreesToRadians(234.0f)), ir*qSin(qDegreesToRadians(234.0f)));

//    poly.clear();
//    poly<<e<<ad<<a<<bd<<b<<cd<<c<<dd<<d<<ed<<e;


//    Q_UNUSED(event);
//    QPainter painter(this);
//    painter.save();
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setBrush(Qt::black);
//    painter.drawRect(rect());
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(Qt::white);

//    for(int i=0;i<5;i++)
//    {
//        painter.resetTransform();
//        painter.translate(r+(w*i),h/2);
//        painter.drawPolygon(poly);
//    }

//    painter.setBrush(Qt::green);
//    for(int i=0;i<rating;i++)
//    {
//        painter.resetTransform();
//        painter.translate(r+(w*i),h/2);
//        painter.drawPolygon(poly);
//    }
//     painter.restore();
//  }

}

QSize StarDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *StarDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
     if(index.column() ==2){
         int starRating = index.data().toInt();
         StarEditor * editor = new StarEditor(parent);
         editor->setStarRating(starRating);
         connect(editor,&StarEditor::editingFinished,this,&StarDelegate::commitAndCloseEditor);
         return editor;
     }else{
         return QStyledItemDelegate::createEditor(parent,option,index);
     }
}

void StarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     if(index.column() ==2){
         int starRating = index.data().toInt();
         StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
         starEditor->setStarRating(starRating);
     }else{
         QStyledItemDelegate::setEditorData(editor,index);
     }
}

void StarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
     if(index.column() ==2){
         StarEditor *starEditor = qobject_cast<StarEditor *>(editor);
         model->setData(index,QVariant::fromValue(starEditor->getStarRating()),
                        Qt::EditRole);
     }else{
         QStyledItemDelegate::setModelData(editor,model,index);
     }

}

void StarDelegate::commitAndCloseEditor()
{
    StarEditor *editor = qobject_cast<StarEditor *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
