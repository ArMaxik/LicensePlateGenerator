#ifndef TEXTUREGENERATOR_H
#define TEXTUREGENERATOR_H

#include <QImage>
#include <QPen>
#include <QBrush>
#include <QPainter>

#include <QFontDatabase>

class TextureGenerator : public QObject
{
    Q_OBJECT
public:
    TextureGenerator();
public slots:
    void generateTexture();
signals:
    void textureGenerated(QImage *diffuse, QImage *normal);
private:
    int id;
};

#endif // TEXTUREGENERATOR_H
