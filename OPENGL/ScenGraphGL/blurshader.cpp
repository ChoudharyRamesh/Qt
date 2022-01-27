//#include "blurshader.h"

//bool CustomShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial)
//{
//    bool changed = false;
//    QByteArray *buf = state.uniformData();
//    Q_ASSERT(buf->size() >= 84);

//    if (state.isMatrixDirty()) {
//        const QMatrix4x4 m = state.combinedMatrix();
//        memcpy(buf->data(), m.constData(), 64);
//        changed = true;
//    }

//    if (state.isOpacityDirty()) {
//        const float opacity = state.opacity();
//        memcpy(buf->data() + 64, &opacity, 4);
//        changed = true;
//    }

//    auto *customMaterial = static_cast<CustomMaterial *>(newMaterial);
//    if (oldMaterial != newMaterial || customMaterial->uniforms.dirty) {
//        memcpy(buf->data() + 68, &customMaterial->uniforms.zoom, 4);
//        memcpy(buf->data() + 72, &customMaterial->uniforms.center, 8);
//        memcpy(buf->data() + 80, &customMaterial->uniforms.limit, 4);
//        customMaterial->uniforms.dirty = false;
//        changed = true;
//    }
//    return changed;
//}
