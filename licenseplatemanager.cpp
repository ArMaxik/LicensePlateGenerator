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

    num = 50;
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
            num--;
            newPlate();
            break;
        }
    }
}

void LicensePlateManager::acceptRenderedImage(QImage img)
{
    QString name = "pic/tmp_";
    if(currentState == state::WaitingOrangeMask) {
        name += "OM_";
    }
    name += QString::number(num) + QString(".png");
    QTextStream(stdout) << name << endl;
    img.save(name);
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
