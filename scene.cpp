#include "scene.h"

Scene::Scene(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , matMan(new MaterialManager())
    , licensePlate(new RenderableEntity(this, matMan->orangeMaskMaterial()))
    , lightMan(new LightManager(this))
    , camera(new Qt3DRender::QCamera(this))
{
    camera->lens()->setPerspectiveProjection(35.0f, 1.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0.0, 25.0, 0.0));
    camera->setViewCenter(QVector3D(0.0, 5.0, 0.0));
    camera->setUpVector(QVector3D(0.0, 1.0, 0.0));
}

MaterialManager *Scene::getMaterialManager() const
{
    return matMan;
}

RenderableEntity *Scene::getRenderableEntity() const
{
    return licensePlate;
}

LightManager *Scene::getLight() const
{
    return lightMan;
}

Qt3DRender::QCamera* Scene::getCamera() const
{
    return camera;
}

void Scene::randomize()
{
    matMan->randomize();
    licensePlate->randomize();
    lightMan->randomize();

    emit changed();
}
