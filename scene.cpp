#include "scene.h"

Scene::Scene(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , matMan(new MaterialManager())
    , licensePlate(new RenderableEntity(this, matMan->orangeMaskMaterial()))
    , light(new Light(this))
    , camera(new Qt3DRender::QCamera(this))
{
    camera->lens()->setOrthographicProjection(-6.0, 6.0, -6.0, 6.0, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 10.0, 0));
    camera->setViewCenter(QVector3D(0, 0, 0));

}

MaterialManager *Scene::getMaterialManager() const
{
    return matMan;
}

RenderableEntity *Scene::getRenderableEntity() const
{
    return licensePlate;
}

Light *Scene::getLight() const
{
    return light;
}

Qt3DRender::QCamera* Scene::getCamera() const
{
    return camera;
}

void Scene::randomize()
{
    matMan->randomize();
    licensePlate->randomize();
    light->randomize();

    emit changed();
}
