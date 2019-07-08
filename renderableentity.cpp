#include "renderableentity.h"

#include <QRandomGenerator>

RenderableEntity::RenderableEntity(Qt3DCore::QNode *parent, Qt3DRender::QMaterial *material)
    : Qt3DCore::QEntity(parent)
    , m_mesh(new Qt3DExtras::QPlaneMesh)
    , m_transform(new Qt3DCore::QTransform())
    , m_material(material)
{
    m_mesh->setHeight(1.0);
    m_mesh->setWidth(2.0);

    m_transform->setScale3D(QVector3D(5.0, 5.0, 5.0));
    m_transform->setRotationX(QRandomGenerator::global()->bounded(-200, 200)/10);
    m_transform->setRotationY(QRandomGenerator::global()->bounded(-200, 200)/10);
    m_transform->setRotationZ(QRandomGenerator::global()->bounded(-200, 200)/10);

    addComponent(m_mesh);
    addComponent(m_transform);
    addComponent(m_material);
}

void RenderableEntity::randomize()
{
    m_transform->setRotationX(QRandomGenerator::global()->bounded(-200, 200)/10);
    m_transform->setRotationY(QRandomGenerator::global()->bounded(-200, 200)/10);
    m_transform->setRotationZ(QRandomGenerator::global()->bounded(-200, 200)/10);
}

void RenderableEntity::setMaterial(Qt3DRender::QMaterial *material)
{
    removeComponent(m_material);
    m_material = material;
    addComponent(m_material);
}
