#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "texturegenerator.h"
#include "material.h"

class MaterialManager : public QObject
{
    Q_OBJECT
public:
    MaterialManager();
    MaterialNormalDiffuseSpecular *floridaPlateMaterial() const;
    MaterialTexture *orangeMaskMaterial() const;

public slots:
    void randomize();

private:
    TextureGenerator texGen;
    MaterialNormalDiffuseSpecular *floridaPlate;
    MaterialTexture *orangeMask;
};

#endif // MATERIALMANAGER_H
