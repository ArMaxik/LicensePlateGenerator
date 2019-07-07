#ifndef MATERIAL_H
#define MATERIAL_H

#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>

#include "imagetexture.h"

class Material : public Qt3DExtras::QNormalDiffuseSpecularMapMaterial
{
    Q_OBJECT
public:
    Material(Qt3DCore::QNode *parent = nullptr);

public slots:
    void setTextures(QImage* diffuse, QImage* normal);

private:
    ImageTexture *m_diffuseTextureImage;
    ImageTexture *m_normalTextureImage;
    ImageTexture *m_specularTextureImage;
};

#endif // MATERIAL_H
