#ifndef LICENSEPLATEMANAGER_H
#define LICENSEPLATEMANAGER_H

#include <QObject>

#include "offscreenengine.h"
#include "scene.h"

class LicensePlateManager : public QObject
{
    Q_OBJECT
public:
    explicit LicensePlateManager(QObject *parent = nullptr);
    Scene *getScene();

signals:
    void imageGenerated(int progress);
    void previewGenerated(QImage *img);



public slots:
    void generate(int number, const QString &_savePath);
    void setRenderSize(const QSize &size);
    void setTextureSize(const QSize &size);
    void stopRender();
    void Preview();

private slots:
    void acceptRenderedImage(QImage img);

private:
    enum state { WaitingPicture, WaitingOrangeMask, Done };
    state currentState;

    void newPlate();
    void configurePlateImage();
    void configureOrangeMask();

    OffscreenEngine *renderEngine;
    Scene *plateScene;

    int num;
    int totalNum;

    QString savePath;
};

#endif // LICENSEPLATEMANAGER_H
