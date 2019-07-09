#ifndef RENDERABLEENTITY_H
#define RENDERABLEENTITY_H


#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPlaneMesh>
#include <QMaterial>

#include "material.h"

class RenderableEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    RenderableEntity(Qt3DCore::QNode *parent = nullptr, Qt3DRender::QMaterial *material = nullptr);

    Qt3DExtras::QPlaneMesh *mesh() const;
    Qt3DCore::QTransform *transform() const;

public slots:
    void randomize();
    void setMaterial(Qt3DRender::QMaterial *material);

private:
    Qt3DExtras::QPlaneMesh *m_mesh;
    Qt3DCore::QTransform *m_transform;
    Qt3DRender::QMaterial *m_material;

};

#endif // RENDERABLEENTITY_H
