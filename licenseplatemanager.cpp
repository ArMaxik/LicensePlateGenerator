#include "licenseplatemanager.h"

LicensePlateManager::LicensePlateManager(QObject *parent)
  : QObject(parent)
  , currentState(state::Done)
{
    plateScene = new Scene();

    renderEngine = new OffscreenEngine(plateScene->getCamera(), QSize(400, 400));
    renderEngine->setSceneRoot(plateScene);

    QObject::connect(renderEngine, &OffscreenEngine::imageRendered,
                     this, &LicensePlateManager::acceptRenderedImage);
    configurePlateImage();
    num = 25;
    savePath = "pic/tmp_";
}

Scene *LicensePlateManager::getScene()
{
    return plateScene;
}

void LicensePlateManager::generate(int number, const QString &_savePath)
{
    totalNum = number;
    num = number;
    savePath = _savePath;
    newPlate();
}

void LicensePlateManager::setRenderSize(const QSize &size)
{

}

void LicensePlateManager::setTextureSize(const QSize &size)
{

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
            emit imageGenerated(totalNum - num);
            newPlate();
            break;
        }
    }
}

void LicensePlateManager::Preview()
{
    plateScene->randomize();
    configurePlateImage();
    renderEngine->requestRenderCapture();
}

void LicensePlateManager::acceptRenderedImage(QImage img)
{
    QString name = savePath;;
    if(currentState == state::WaitingOrangeMask) {
        name += "OM_";
    }
    name += QString::number(num) + QString(".png");
//    QTextStream(stdout) << name << endl;
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
