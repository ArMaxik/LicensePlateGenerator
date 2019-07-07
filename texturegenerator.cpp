#include "texturegenerator.h"

#include <QRandomGenerator>
#include <QVector3D>

QString gen_random_main_label(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    QString res;

    for (int i = 0; i < len; ++i) {
        res += alphanum[QRandomGenerator::global()->bounded((int)sizeof(alphanum)-1)];
    }

    return res;
}

QString gen_random_small_str(const int min, const int max) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    QString res;
    int spaces = 0;
    bool was_space = false;
    int len = QRandomGenerator::global()->bounded(min, max);

    for (int i = 0; i < len; ++i) {
        if (!was_space && i != min && i != max - 1 && spaces < 4 && QRandomGenerator::global()->bounded(100) < 25) {
            res += ' ';
            was_space = true;
        }
        else {
            res += alphanum[rand() % (sizeof(alphanum) - 1)];
            was_space = false;
        }
    }

    return res;
}

TextureGenerator::TextureGenerator()
{
    id = QFontDatabase::addApplicationFont(":/fonts/PlateFont.ttf");
}

QVector<int> getBlackNeighComps(QImage *img, int x, int y)
{
    static QPoint indexes[] = {
        QPoint(-1, +1), // 0
        QPoint( 0, +1), // 1
        QPoint(+1, +1), // 2
        QPoint(-1,  0), // 3
        QPoint( 0,  0), // 4
        QPoint(+1,  0), // 5
        QPoint(-1, -1), // 6
        QPoint( 0, -1), // 7
        QPoint(+1, -1)  // 8
    };
    QVector<int> res(9, 0);
    for(int i = 0; i < 9; i++) {
        if(indexes[i].x() + x >= img->width()) continue;
        if(indexes[i].y() + y >= img->height()) continue;
        if(indexes[i].x() + x < 0) continue;
        if(indexes[i].y() + y < 0) continue;
        res[i] = img->pixelColor(indexes[i] + QPoint(x, y)).black();
    }
    return res;
}

QImage* height2Normal(QImage *img)
{
    QImage *normal = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterD(normal);

    static float scale = 1.0;
    for(int i = 0; i < img->height(); i++) {
        for(int j = 0; j < img->width(); j++) {
            QVector3D n;
            auto s = getBlackNeighComps(img, j, i);
            n.setX(scale * -(s[2]-s[0]+2*(s[5]-s[3])+s[8]-s[6]));
            n.setY(scale * -(s[6]-s[0]+2*(s[7]-s[1])+s[8]-s[2]));
            n.setZ(1.0);
            n.normalize();
            n.setX((n.x()+1) * 255.0 / 2.0);
            n.setY((n.y()+1) * 255.0 / 2.0);
            n.setZ((n.z() * 127.0 + 128.0));
            if(n.x() < 0.0 || n.x() > 255.0)
                qWarning("HERE X");
            if(n.y() < 0.0 || n.y() > 255.0)
                qWarning("HERE Y");
            if(n.z() < 0.0 || n.z() > 255.0)
                qWarning("HERE Z");
            normal->setPixelColor(j, i, QColor(n.x(), n.y(), n.z()));
        }
    }
    return normal;
}

void TextureGenerator::generateTexture()
{
    QImage *diffuse = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterD(diffuse);
    QImage *height = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterN(height);

    QString mainLbl1 = gen_random_main_label(3);
    QString mainLbl2 = gen_random_main_label(3);
    QString smallLbl = gen_random_small_str(6, 12);

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    // Diffuse
    QImage back("C:/Users/slava/OneDrive/Job/pic/MyFLORIDA_small.png");
    painterD.drawImage(QPoint(0, 0), back);

    font.setPixelSize(68);
    painterD.setFont(font);
    painterD.setPen(QColor(17, 141, 128));

    painterD.drawText(12, 42, 280, 140, 0, mainLbl1);
    painterD.drawText(175, 42, 280, 140, 0, mainLbl2);

    font.setPixelSize(18);
    painterD.setFont(font);
    painterD.drawText(0, 118, 280, 140, Qt::AlignHCenter, smallLbl);

    // Normal
    painterN.setPen(Qt::white);
    painterN.setBrush(Qt::white);
    painterN.drawRect(height->rect());

    painterN.setPen(Qt::black);
    font.setPixelSize(68);
    painterN.setFont(font);

    painterN.drawText(12, 42, 280, 140, 0, mainLbl1);
    painterN.drawText(175, 42, 280, 140, 0, mainLbl2);

    font.setPixelSize(18);
    painterN.setFont(font);
    painterN.drawText(0, 118, 280, 140, Qt::AlignHCenter, smallLbl);

    QImage *normal = height2Normal(height);
    painterN.end();
    delete height;
    emit textureGenerated(diffuse, normal);
}
