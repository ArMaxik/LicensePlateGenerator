#ifndef SCENE_H
#define SCENE_H

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>

#include "materialmanager.h"
#include "renderableentity.h"
#include "light.h"

class Scene : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    Scene(Qt3DCore::QNode *parent = nullptr);

    MaterialManager *getMaterialManager() const;
    RenderableEntity *getRenderableEntity() const;
    Light *getLight() const;
    Qt3DRender::QCamera *getCamera() const;

signals:
    void changed();

public slots:
    void randomize();

private:
    MaterialManager *matMan;
    RenderableEntity *licensePlate;
    Light *light;
    Qt3DRender::QCamera *camera;
};

#endif // SCENE_H
