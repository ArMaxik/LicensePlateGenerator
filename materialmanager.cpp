#include "materialmanager.h"

MaterialManager::MaterialManager()
    : floridaPlate(new MaterialNormalDiffuseSpecular())
    , orangeMask(new MaterialTexture())
{
    QObject::connect(&texGen, &TextureGenerator::diffuseGenerated,
                         floridaPlate->getDiffuseTexture(), &ImageTexture::setImage);
    QObject::connect(&texGen, &TextureGenerator::normalGenerated,
                     floridaPlate->getNormalTexture(), &ImageTexture::setImage);
    QObject::connect(&texGen, &TextureGenerator::orangeMaskGenerated,
                     orangeMask->getTexture(), &ImageTexture::setImage);
}

MaterialNormalDiffuseSpecular *MaterialManager::floridaPlateMaterial() const
{
    return floridaPlate;
}

MaterialTexture *MaterialManager::orangeMaskMaterial() const
{
    return orangeMask;
}

TextureGenerator *MaterialManager::getGenerator()
{
    return &texGen;
}

void MaterialManager::randomize()
{
    texGen.generateTexture();
}
