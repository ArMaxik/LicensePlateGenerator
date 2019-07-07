#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "texturegenerator.h"
#include "material.h"

class MaterialManager : public QObject
{
    Q_OBJECT
public:
    MaterialManager();
    Material *material() const;

public slots:
    void randomize();

private:
    TextureGenerator texGen;
    Material *floridaPlate;
};

#endif // MATERIALMANAGER_H
