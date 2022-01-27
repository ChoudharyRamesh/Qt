#ifndef TRIANGLE_H
#define TRIANGLE_H

#include<QQuickItem>
#include<QMatrix4x4>
#include<QSGGeometryNode>
#include<QSGGeometry>
#include<QSGFlatColorMaterial>
#include<QSGSimpleTextureNode>
#include<QSGOpacityNode>

class Triangle:public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal imageRotation READ imageRotation WRITE setImageRotation NOTIFY imageRotationChanged)
    Q_PROPERTY(qreal imageScaleX READ imageScaleX WRITE setImageScaleX NOTIFY imageScaleXChanged)
    Q_PROPERTY(qreal imageScaleY READ imageScaleY WRITE setImageScaleY NOTIFY imageScaleYChanged)
    Q_PROPERTY(bool magicFilter READ magicFilter WRITE setMagicFilter NOTIFY magicFilterChanged)

public:
    Triangle();

    qreal imageRotation() const;
    void setImageRotation(qreal newImageRotation);

    qreal imageScaleX() const;
    void setImageScaleX(qreal newImageScaleX);

    qreal imageScaleY() const;
    void setImageScaleY(qreal newImageScaleY);

    bool magicFilter() const;
    void setMagicFilter(bool newMagicFilter);

signals:
    void imageRotationChanged();
    void imageScaleXChanged();
    void imageScaleYChanged();

    void magicFilterChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    QMatrix4x4 mat;
    qreal m_imageRotation=0;
    QSize imageSize;
    QSGTexture * texture;

    qreal m_imageScaleX=1;
    qreal m_imageScaleY=1;
    bool m_magicFilter;
};

#endif // TRIANGLE_H
