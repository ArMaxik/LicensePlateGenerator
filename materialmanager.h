#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "texturegenerator.h"
#include "material.h"

class MaterialManager : public QObject
{
    Q_OBJECT
public:
    MaterialManager(QObject *parent = nullptr);
    MaterialNormalDiffuseSpecular *floridaPlateMaterial() const;
    MaterialTexture *orangeMaskMaterial() const;
    TextureGenerator *getGenerator() const;

public slots:
    void randomize();

private:
    TextureGenerator *texGen;
    MaterialNormalDiffuseSpecular *floridaPlate;
    MaterialTexture *orangeMask;
};

#endif // MATERIALMANAGER_H
