#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H
#include <QQuickItem>

class CustomItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(int iterationLimit READ iterationLimit WRITE setIterationLimit NOTIFY iterationLimitChanged)
    Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)

public:
    explicit CustomItem(QQuickItem *parent = 0);

    qreal zoom() const
    {
        return m_zoom;
    }

    int iterationLimit() const
    {
        return m_limit;
    }

    QPointF center() const
    {
        return m_center;
    }

public slots:
    void setZoom(qreal zoom);

    void setIterationLimit(int iterationLimit);

    void setCenter(QPointF center);

signals:
    void zoomChanged(qreal zoom);

    void iterationLimitChanged(int iterationLimit);

    void centerChanged(QPointF center);

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    bool m_geometryChanged = true;
    qreal m_zoom;
    bool m_zoomChanged = true;
    int m_limit;
    bool m_limitChanged = true;
    QPointF m_center;
    bool m_centerChanged = true;
};
#endif // CUSTOMITEM_H
