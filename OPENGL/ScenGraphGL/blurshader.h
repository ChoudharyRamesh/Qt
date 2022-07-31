//#ifndef BLURSHADER_H
//#define BLURSHADER_H

//class CustomShader : public QSGMaterialShader
//{
//public:
//    CustomShader()
//    {
//        setShaderFileName(VertexStage, QLatin1String(":/scenegraph/custommaterial/shaders/mandelbrot.vert.qsb"));
//        setShaderFileName(FragmentStage, QLatin1String(":/scenegraph/custommaterial/shaders/mandelbrot.frag.qsb"));
//    }
//    bool updateUniformData(RenderState &state,
//                           QSGMaterial *newMaterial, QSGMaterial *oldMaterial) override;
//};


//class CustomMaterial : public QSGMaterial
//{
//public:
//    CustomMaterial();
//    QSGMaterialType *type() const override;
//    int compare(const QSGMaterial *other) const override;

//    QSGMaterialShader *createShader(QSGRendererInterface::RenderMode) const override
//    {
//        return new CustomShader;
//    }

//    struct {
//        float center[2];
//        float zoom;
//        int limit;
//        bool dirty;
//    } uniforms;
//};


//#endif // BLURSHADER_H
