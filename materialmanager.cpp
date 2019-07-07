#include "materialmanager.h"

MaterialManager::MaterialManager()
    : floridaPlate(new Material())
{
    QObject::connect(&texGen, &TextureGenerator::textureGenerated,
                         floridaPlate, &Material::setTextures);
}

Material *MaterialManager::material() const
{
    return floridaPlate;
}

void MaterialManager::randomize()
{
    texGen.generateTexture();
}
