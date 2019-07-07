#include "light.h"

#include <QRandomGenerator>

Light::Light(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_light(new Qt3DRender::QPointLight())
    , m_transform(new Qt3DCore::QTransform())
{
    m_light->setIntensity(1.0);
    m_light->setColor(Qt::white);

    m_transform->setTranslation(QVector3D(0.0, 10.0, 0.0));

    addComponent(m_light);
    addComponent(m_transform);
}

void Light::randomize()
{
    m_light->setColor(QColor(QRandomGenerator::global()->bounded(200, 256),
                             QRandomGenerator::global()->bounded(200, 256),
                             QRandomGenerator::global()->bounded(200, 256)));
    m_light->setIntensity(QRandomGenerator::global()->bounded(2, 15)/10.0);

    m_transform->setTranslation(QVector3D(QRandomGenerator::global()->bounded(-100, 100)/10,
                                             10.0,
                                             QRandomGenerator::global()->bounded(-100, 100)/10));
}
