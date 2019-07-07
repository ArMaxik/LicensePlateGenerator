#include "material.h"

Material::Material(Qt3DCore::QNode *parent)
    : Qt3DExtras::QNormalDiffuseSpecularMapMaterial(parent)
    , m_diffuseTextureImage(new ImageTexture())
    , m_normalTextureImage(new ImageTexture())
    , m_specularTextureImage(new ImageTexture())
{
    diffuse()->addTextureImage(m_diffuseTextureImage);
    normal()->addTextureImage(m_normalTextureImage);
    specular()->addTextureImage(m_specularTextureImage);
}

void Material::setTextures(QImage *diffuse, QImage *normal)
{
    m_diffuseTextureImage->setImage(diffuse);
    m_normalTextureImage->setImage(normal);
//    m_specularTextureImage->setImage(specular);

    m_diffuseTextureImage->update();
    m_normalTextureImage->update();
    m_specularTextureImage->update();
}
