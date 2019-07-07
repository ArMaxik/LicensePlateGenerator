#ifndef LIGHT_H
#define LIGHT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <QPointLight>


class Light : public Qt3DCore::QEntity
{
public:
    Light(Qt3DCore::QNode *parent = nullptr);

public slots:
    void randomize();

private:
    Qt3DCore::QTransform *m_transform;
    Qt3DRender::QPointLight *m_light;
};

#endif // LIGHT_H
