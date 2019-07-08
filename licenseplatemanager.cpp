#include "licenseplatemanager.h"

LicensePlateManager::LicensePlateManager(QObject *parent)
  : QObject(parent)
  , currentState(state::Done)
{
    plateScene = new Scene();

    renderEngine = new OffscreenEngine(plateScene->getCamera(), QSize(400, 400));
    renderEngine->setSceneRoot(plateScene);

//    QObject::connect(plateScene, &Scene::changed,
//                     renderEngine, &OffscreenEngine::requestRenderCapture);
    QObject::connect(renderEngine, &OffscreenEngine::imageRendered,
                     this, &LicensePlateManager::acceptRenderedImage);

    num = 3;
}

void LicensePlateManager::newPlate()
{
    if(num > 0)
    {
        switch (currentState) {
        case state::Done:
            plateScene->randomize();
            configurePlateImage();
            currentState = state::WaitingPicture;
            renderEngine->requestRenderCapture();
            break;
        case state::WaitingPicture:
            configureOrangeMask();
            currentState = state::WaitingOrangeMask;
            renderEngine->requestRenderCapture();
            break;
        case state::WaitingOrangeMask:
            currentState = state::Done;
            newPlate();
            break;
        }
    }
}

void LicensePlateManager::acceptRenderedImage(QImage img)
{
    QTextStream(stdout) << QString("pic/tmp") + QString::number(num) + QString(".png") << endl;
    img.save(QString("pic/tmp") + QString::number(num--) + QString(".png"));
    newPlate();
}

void LicensePlateManager::configurePlateImage()
{
    plateScene->getRenderableEntity()->setMaterial(plateScene->getMaterialManager()->floridaPlateMaterial());
    renderEngine->setClearColor(QColor(100, 100, 100, 255));
}

void LicensePlateManager::configureOrangeMask()
{
     plateScene->getRenderableEntity()->setMaterial(plateScene->getMaterialManager()->orangeMaskMaterial());
     renderEngine->setClearColor(Qt::black);
}
