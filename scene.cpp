#include "scene.h"

Scene::Scene(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , matMan(new MaterialManager())
    , licensePlate(new RenderableEntity(this, matMan->material()))
    , light(new Light(this))
{
//    licensePlate = new RenderableEntity(this, matMan->material());
}

void Scene::randomize()
{
    matMan->randomize();
    licensePlate->randomize();
    light->randomize();
}
