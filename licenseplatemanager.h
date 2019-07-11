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
    ~LicensePlateManager();
    Scene *getScene();

signals:
    void imageGenerated(int progress);

public slots:
    void generate(int number, const QString &_savePath);
    void stopRender();
    void setRenderSize(const QSize &size);  // Не реализовано
    void setTextureSize(const QSize &size); // Не реализовано
    void Preview();                         // Не реализовано

private slots:
    void acceptRenderedImage(QImage img);

private:
    enum state { WaitingPicture, WaitingOrangeMask, Done };
    state currentState;

    void newPlate();
    void configurePlateImage();  // Обычное изображение номера
    void configureOrangeMask();  // Маска апельсина

    OffscreenEngine *renderEngine;
    Scene *plateScene;

    int rendersNumber;
    int totalRenders;

    QString savePath;
};

#endif // LICENSEPLATEMANAGER_H
