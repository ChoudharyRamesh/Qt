#include "triangle.h"

Triangle::Triangle()
{
    setFlag(QQuickItem::ItemHasContents);

}

QSGNode * Triangle::updatePaintNode(QSGNode * oldNode , UpdatePaintNodeData * data )
{
    Q_UNUSED(data)
    QSGSimpleTextureNode * textureNode;
    QSGTransformNode * transformNode;
    QSGNode * rootNode;
    if(!oldNode)
    {
        rootNode = new QSGNode;

        transformNode = new QSGTransformNode();
        transformNode->setFlag(QSGNode::OwnedByParent,true);
        QImage image(":/Image/me2.jpg");
        imageSize = image.size();
        texture = window()->createTextureFromImage(image);
        textureNode = new QSGSimpleTextureNode();
        textureNode->setTexture(texture);
        textureNode->setOwnsTexture(true);
        textureNode->setFlag(QSGNode::OwnedByParent,true);

        rootNode->appendChildNode(transformNode);
        transformNode->appendChildNode(textureNode);

    }
    else
    {
        transformNode =  static_cast<QSGTransformNode *>(oldNode->firstChild());
        textureNode =  static_cast<QSGSimpleTextureNode *>(transformNode->firstChild());
        rootNode= oldNode;
    }

    QSize newRenderSize = imageSize.scaled(width(),height(),Qt::KeepAspectRatio);
    QRectF renderRect(width()/2 - newRenderSize.width()/2 ,
                      height()/2- newRenderSize.height()/2
                      ,newRenderSize.width(),newRenderSize.height());


    QRectF rotatedRect = QTransform().rotate(m_imageRotation).mapRect(renderRect);
    qreal a = std::min(boundingRect().width()/rotatedRect.width() , boundingRect().height()/rotatedRect.height());

    mat.setToIdentity();
    mat.translate(width()/2,height()/2,0);
    mat.rotate(m_imageRotation,0,0,1);
    mat.scale(a,a);
    mat.scale(m_imageScaleX,m_imageScaleY);
    mat.translate(-width()/2,-height()/2,0);

    transformNode->setMatrix(mat);
    textureNode->setRect(renderRect);

    return rootNode;
}

qreal Triangle::imageRotation() const
{
    return m_imageRotation;
}

void Triangle::setImageRotation(qreal newImageRotation)
{
    if (qFuzzyCompare(m_imageRotation, newImageRotation)) return;
    m_imageRotation = newImageRotation;
    update();
    emit imageRotationChanged();
}

qreal Triangle::imageScaleX() const
{
    return m_imageScaleX;
}

void Triangle::setImageScaleX(qreal newImageScaleX)
{
    if (qFuzzyCompare(m_imageScaleX, newImageScaleX)) return;
    m_imageScaleX = newImageScaleX;
    update();
    emit imageScaleXChanged();
}


qreal Triangle::imageScaleY() const
{
    return m_imageScaleY;
}

void Triangle::setImageScaleY(qreal newImageScaleY)
{
    if (qFuzzyCompare(m_imageScaleY, newImageScaleY)) return;
    m_imageScaleY = newImageScaleY;
    update();
    emit imageScaleYChanged();
}

bool Triangle::magicFilter() const
{
    return m_magicFilter;
}

void Triangle::setMagicFilter(bool newMagicFilter)
{
    if (m_magicFilter == newMagicFilter) return;
    m_magicFilter = newMagicFilter;
    emit magicFilterChanged();
}















//QSGNode *Triangle::updatePaintNode(QSGNode * oldNode , UpdatePaintNodeData * data )
//{
//    QSGGeometryNode * node;
//    QSGGeometry * geometry;
//    int vertexCount = 4;
//    if(!oldNode)
//    {
//        node = new QSGGeometryNode;
//        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),vertexCount,0);
//        node->setGeometry(geometry);
//        node->setFlag(QSGNode::OwnsGeometry);
//        geometry->setDrawingMode(QSGGeometry::DrawTriangles);
//        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
//        material->setColor(QColor(255, 0, 0));
//        node->setMaterial(material);
//        node->setFlag(QSGNode::OwnsMaterial);
//    }
//    else
//    {
//        node = static_cast<QSGGeometryNode *>(oldNode);
//        geometry = node->geometry();
//        geometry->allocate(vertexCount);
//    }

//    QSGGeometry::Point2D * vertices = geometry->vertexDataAsPoint2D();

//    vertices[0].set(0,height());
//    vertices[1].set(width()/2,0);
//    vertices[2].set(width(),height());

//    return node;
//}

//QSGNode *Triangle::updatePaintNode(QSGNode * oldNode , UpdatePaintNodeData * data )
//{
//    QSGGeometryNode * node;
//    QSGGeometry * geometry;
//    int vertexCount = 4;
//    int indexCount = 6;
//    if(!oldNode)
//    {
//        node = new QSGGeometryNode;
//        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),vertexCount,indexCount);
//        node->setGeometry(geometry);
//        node->setFlag(QSGNode::OwnsGeometry);
//        geometry->setDrawingMode(QSGGeometry::DrawTriangles);
//        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
//        material->setColor(QColor(255, 0, 0));
//        node->setMaterial(material);
//        node->setFlag(QSGNode::OwnsMaterial);
//    }
//    else
//    {
//        node = static_cast<QSGGeometryNode *>(oldNode);
//        geometry = node->geometry();
//        geometry->allocate(vertexCount);
//    }

//    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

//    vertices[0].set(0,0);
//    vertices[1].set(width(),0);
//    vertices[2].set(width(),height());
//    vertices[3].set(0,height());

//    quint16 *  indices = geometry->indexDataAsUShort();
//    indices[0]=0;  indices[1]=1;  indices[2]=2;
//    indices[3]=2;  indices[4]=3;  indices[5]=0;

//    return node;
//}



