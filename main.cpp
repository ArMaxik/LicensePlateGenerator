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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    Qt3DExtras::Qt3DWindow view;

//    QWidget *widget = new QWidget;
//    widget->setWindowTitle(QStringLiteral("Florida plates"));

//    QWidget *container = QWidget::createWindowContainer(&view);
//    container->setMinimumSize(QSize(400, 400));
//    container->setMaximumSize(QSize(400, 400));

//    QPushButton *genButton = new QPushButton();
//    genButton->setText("Generate");
//    genButton->setMaximumWidth(100);

//    QHBoxLayout *hLayout = new QHBoxLayout(widget);
//    hLayout->addWidget(container);
//    hLayout->addWidget(genButton);

//    Scene *rootS = new Scene();
//    rootS->randomize();

//    QObject::connect(genButton, &QPushButton::clicked, rootS, &Scene::randomize);

//    // Camera
//    Qt3DRender::QCamera *camera = view.camera();
//    camera->lens()->setOrthographicProjection(-6.0, 6.0, -6.0, 6.0, 0.1f, 1000.0f);
//    camera->setPosition(QVector3D(0, 10.0, 0));
//    camera->setViewCenter(QVector3D(0, 0, 0));

//    view.setRootEntity(rootS);

//    widget->show();

    LicensePlateManager lpm;

    //lpm.newPlate();
    TextureView *tv = new TextureView;

    QWidget *widget = new QWidget;

    QPushButton *genButton = new QPushButton();
    genButton->setText("Generate");
    genButton->setMaximumWidth(100);
    QPushButton *prevButton = new QPushButton();
    prevButton->setText("Preview");
    prevButton->setMaximumWidth(100);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->setMargin(150);
    hLayout->addWidget(genButton);
    hLayout->addWidget(prevButton);
    QObject::connect(genButton, &QPushButton::clicked, &lpm, &LicensePlateManager::newPlate);
    QObject::connect(prevButton, &QPushButton::clicked, &lpm, &LicensePlateManager::Preview);

    QObject::connect(lpm.getScene()->getMaterialManager()->getGenerator(), &TextureGenerator::diffuseGenerated,
                     tv, &TextureView::setImageD);
    QObject::connect(lpm.getScene()->getMaterialManager()->getGenerator(), &TextureGenerator::heightGenerated,
                     tv, &TextureView::setImageH);
    QObject::connect(lpm.getScene()->getMaterialManager()->getGenerator(), &TextureGenerator::normalGenerated,
                     tv, &TextureView::setImageN);

    widget->show();
    tv->show();


    return app.exec();
}
