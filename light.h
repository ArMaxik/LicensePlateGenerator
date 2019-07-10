#ifndef LIGHT_H
#define LIGHT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <QPointLight>
#include <QDirectionalLight>


class PointLight : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    PointLight(Qt3DCore::QNode *parent = nullptr);
    Qt3DRender::QPointLight *getLight();
    Qt3DCore::QTransform *getTransform();

public slots:
    void randomize();

private:
    Qt3DRender::QPointLight *m_light;
    Qt3DCore::QTransform *m_transform;
};


class DirectionalLight : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    DirectionalLight(Qt3DCore::QNode *parent = nullptr);
    Qt3DRender::QDirectionalLight *getLight();

public slots:
    void randomize();

private:
    Qt3DCore::QTransform *m_transform;
    Qt3DRender::QDirectionalLight *m_light;
};

class LightManager : public QObject
{
    Q_OBJECT
public:
    LightManager(Qt3DCore::QEntity *rootEntity, QObject *parent = nullptr);

public slots:
    void randomize();

private:
    PointLight *mainLight;
    DirectionalLight *ambient1;
    DirectionalLight *ambient2;
};

#endif // LIGHT_H
