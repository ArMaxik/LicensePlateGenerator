#ifndef SCENE_H
#define SCENE_H

#include <Qt3DCore/QEntity>

#include "materialmanager.h"
#include "renderableentity.h"
#include "light.h"

class Scene : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    Scene(Qt3DCore::QNode *parent = nullptr);

public slots:
    void randomize();

private:
    MaterialManager *matMan;
    RenderableEntity *licensePlate;
    Light *light;
};

#endif // SCENE_H
