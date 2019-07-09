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

public slots:
    void newPlate();
    void Preview();

private slots:
    void acceptRenderedImage(QImage img);

private:
    enum state { WaitingPicture, WaitingOrangeMask, Done };
    state currentState;

    void configurePlateImage();
    void configureOrangeMask();

    OffscreenEngine *renderEngine;
    Scene *plateScene;

    int num;
};

#endif // LICENSEPLATEMANAGER_H
