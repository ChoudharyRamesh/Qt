
#include "customitem.h"
#include <QtCore/QPointer>
#include <QtQuick/QSGMaterial>
#include <QtQuick/QSGTexture>
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGTextureProvider>

class CustomShader : public QSGMaterialShader
{
public:
    CustomShader()
    {
        setShaderFileName(VertexStage,":/SceneGraphGL3/Shaders/shader.vert.qsb");
        setShaderFileName(FragmentStage,":/SceneGraphGL3/Shaders/shader.frag.qsb");
    }
    bool updateUniformData(RenderState &state,
                           QSGMaterial *newMaterial, QSGMaterial *oldMaterial) override;
};


class CustomMaterial : public QSGMaterial
{
public:
    CustomMaterial(){}
    QSGMaterialType *type() const override
    {
        static QSGMaterialType type;
        return &type;
    }

    int compare(const QSGMaterial * other) const override
    {
        Q_ASSERT(other && type() == other->type());
        const auto *other2 = static_cast<const CustomMaterial *>(other);
        return other2 == this ? 0 : 1; // ### TODO: compare state???
    }

    QSGMaterialShader *createShader(QSGRendererInterface::RenderMode) const override
    {
        return new CustomShader;
    }

    struct {
        float center[2];
        float zoom;
        int limit;
        bool dirty;
    } uniforms;
};



bool CustomShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial)
{
    bool changed = false;
    QByteArray *buf = state.uniformData();
    Q_ASSERT(buf->size() >= 84);

    if (state.isMatrixDirty()) {
        const QMatrix4x4 m = state.combinedMatrix();
        memcpy(buf->data(), m.constData(), 64);
        changed = true;
    }

    if (state.isOpacityDirty()) {
        const float opacity = state.opacity();
        memcpy(buf->data() + 64, &opacity, 4);
        changed = true;
    }

    auto *customMaterial = static_cast<CustomMaterial *>(newMaterial);
    if (oldMaterial != newMaterial || customMaterial->uniforms.dirty) {
        memcpy(buf->data() + 68, &customMaterial->uniforms.zoom, 4);
        memcpy(buf->data() + 72, &customMaterial->uniforms.center, 8);
        memcpy(buf->data() + 80, &customMaterial->uniforms.limit, 4);
        customMaterial->uniforms.dirty = false;
        changed = true;
    }
    return changed;
}

class CustomNode : public QSGGeometryNode
{
public:
    CustomNode()
    {
        auto *m = new CustomMaterial;
        setMaterial(m);
        setFlag(OwnsMaterial, true);

        QSGGeometry *g = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4);
        QSGGeometry::updateTexturedRectGeometry(g, QRect(), QRect());
        setGeometry(g);
        setFlag(OwnsGeometry, true);
    }

    void setRect(const QRectF &bounds)
    {
        QSGGeometry::updateTexturedRectGeometry(geometry(), bounds, QRectF(0, 0, 1, 1));
        markDirty(QSGNode::DirtyGeometry);
    }

    void setZoom(qreal zoom)
    {
        auto *m = static_cast<CustomMaterial *>(material());
        m->uniforms.zoom = zoom;
        m->uniforms.dirty = true;
        markDirty(DirtyMaterial);
    }

    void setLimit(int limit)
    {
        auto *m = static_cast<CustomMaterial *>(material());
        m->uniforms.limit = limit;
        m->uniforms.dirty = true;
        markDirty(DirtyMaterial);
    }

    void setCenter(const QPointF &center)
    {
        auto *m = static_cast<CustomMaterial *>(material());
        m->uniforms.center[0] = center.x();
        m->uniforms.center[1] = center.y();
        m->uniforms.dirty = true;
        markDirty(DirtyMaterial);
    }
};


CustomItem::CustomItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}


void CustomItem::setZoom(qreal zoom)
{
    if (qFuzzyCompare(m_zoom, zoom))
        return;

    m_zoom = zoom;
    m_zoomChanged = true;
    emit zoomChanged(m_zoom);
    update();
}

void CustomItem::setIterationLimit(int limit)
{
    if (m_limit == limit)
        return;

    m_limit = limit;
    m_limitChanged = true;
    emit iterationLimitChanged(m_limit);
    update();
}

void CustomItem::setCenter(QPointF center)
{
    if (m_center == center)
        return;

    m_center = center;
    m_centerChanged = true;
    emit centerChanged(m_center);
    update();
}


void CustomItem::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChange(newGeometry, oldGeometry);
}

QSGNode *CustomItem::updatePaintNode(QSGNode *old, UpdatePaintNodeData *)
{
    auto *node = static_cast<CustomNode *>(old);

    if (!node)
        node = new CustomNode;

    if (m_geometryChanged)
        node->setRect(boundingRect());
    m_geometryChanged = false;

    if (m_zoomChanged)
        node->setZoom(m_zoom);
    m_zoomChanged = false;

    if (m_limitChanged)
        node->setLimit(m_limit);
    m_limitChanged = false;

    if (m_centerChanged)
        node->setCenter(m_center);
    m_centerChanged = false;

    return node;
}
