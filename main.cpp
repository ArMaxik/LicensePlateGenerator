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
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(32);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);


    MainWidget mw;

    mw.show();

    return app.exec();
}
