#include <QApplication>

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <QPushButton>
#include <QHBoxLayout>

#include "qt3dwindow.h"
#include "scene.h"

#include "licenseplatemanager.h"
#include "textureview.h"
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(32);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

//    LicensePlateManager lpm;

//    TextureView *tv = new TextureView;

//    QWidget *widget = new QWidget;

//    QPushButton *genButton = new QPushButton();
//    genButton->setText("Generate");
//    genButton->setMaximumWidth(100);
//    QPushButton *prevButton = new QPushButton();
//    prevButton->setText("Preview");
//    prevButton->setMaximumWidth(100);
//    QHBoxLayout *hLayout = new QHBoxLayout(widget);
//    hLayout->setMargin(150);
//    hLayout->addWidget(genButton);
//    hLayout->addWidget(prevButton);
//    QObject::connect(genButton, &QPushButton::clicked, &lpm, &LicensePlateManager::newPlate);
//    QObject::connect(prevButton, &QPushButton::clicked, &lpm, &LicensePlateManager::Preview);

//    QObject::connect(lpm.getScene()->getMaterialManager()->getGenerator(), &TextureGenerator::diffuseGenerated,
//                     tv, &TextureView::setImageD);
//    QObject::connect(lpm.getScene()->getMaterialManager()->getGenerator(), &TextureGenerator::heightGenerated,
//                     tv, &TextureView::setImageH);
//    QObject::connect(lpm.getScene()->getMaterialManager()->getGenerator(), &TextureGenerator::normalGenerated,
//                     tv, &TextureView::setImageN);
//    widget->show();
//    tv->show();

    MainWidget mw;

    mw.show();

    return app.exec();
}
