#include "texturegenerator.h"

#include <QRandomGenerator>
#include <QVector3D>
#include <QtMath>

QString gen_random_main_label1() {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    QString res;

    for (int i = 0; i < 3; ++i) {
        res += alphanum[QRandomGenerator::global()->bounded((int)sizeof(alphanum)-1)];
    }

    return res;
}

QString gen_random_main_label2() {
    static const char num[] =
            "0123456789";
    static const char alpha[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    QString res;
    res += alpha[QRandomGenerator::global()->bounded((int)sizeof(alpha)-1)];
    for (int i = 0; i < 2; ++i) {
        res += num[QRandomGenerator::global()->bounded((int)sizeof(num)-1)];
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
    id = QFontDatabase::addApplicationFont(":/fonts/Driver Gothic.otf");
}

QVector<int> boxesForGauss(double sigma, int n)  // standard deviation, number of boxes
{
    double wIdeal = qSqrt((12.0 * sigma * sigma/n) + 1.0);  // Ideal averaging filter width
    int wl = qFloor(wIdeal);
    if(wl % 2 == 0) wl--;
    int wu = wl+2;

    double mIdeal = (12.0*sigma*sigma - n*wl*wl - 4.0*n*wl - 3*n) / (-4.0*wl - 4.0);
    int m = qRound(mIdeal);

    QVector<int> sizes;
    for(int i=0; i < n; i++)
    {
        sizes.append(i < m ? wl : wu);
    }
    return sizes;
}
// source channel, radius
void boxBlur(QImage* scr, QImage* res, int r) {
    int w = scr->size().width();
    int h = scr->size().height();
//    QImage *blurred = new QImage(280, 140, QImage::Format_RGB32);
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) {
            int val = 0;
            for(int iy = i-r; iy < i+r+1; iy++)
                for(int ix = j-r; ix < j+r+1; ix++) {
                    int x = qMin(w-1, qMax(0, ix));
                    int y = qMin(h-1, qMax(0, iy));
                    val += scr->pixelColor(x, y).black();
                }
            val = val/((r+r+1)*(r+r+1));
            res->setPixelColor(j, i, QColor(val, val, val));
        }
}
// source channel, radius
QImage* gaussBlur (QImage* scr, int r) {
    QVector<int> bxs = boxesForGauss(r, 3);
    QImage *blurred = new QImage(280, 140, QImage::Format_RGB32);

    boxBlur(scr, blurred, (bxs[0]-1)/2);
    boxBlur(blurred, scr, (bxs[1]-1)/2);
    boxBlur(scr, blurred, (bxs[2]-1)/2);

    return blurred;
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

QImage* height2Normal(QImage *height)
{
    QImage *normal = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterD(normal);

    static float scale = 0.003f;
    for(int i = 0; i < height->height(); i++) {
        for(int j = 0; j < height->width(); j++) {
            QVector3D n;
            auto s = getBlackNeighComps(height, j, i);
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

void drawText(QPainter &painter, QFont &font, const QColor &color, QString &mainLbl1, QString &mainLbl2, QString &smallLbl) {
    const int bigLblSize = 85;
    const int smallLblSize = 20;
    font.setPixelSize(bigLblSize);
    font.setLetterSpacing(QFont::PercentageSpacing, 100);
    font.setBold(false);
    painter.setFont(font);
    painter.setPen(color);

    painter.drawText(12, 22, 280, 140, 0, mainLbl1);
    font.setLetterSpacing(QFont::PercentageSpacing, 95);
    painter.setFont(font);
    painter.drawText(170, 22, 280, 140, 0, mainLbl2);

    font.setPixelSize(smallLblSize);
    font.setLetterSpacing(QFont::PercentageSpacing, 120);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(0, 115, 280, 140, Qt::AlignHCenter, smallLbl);
}

void TextureGenerator::generateTexture()
{

    QImage *diffuse = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterD(diffuse);
    QImage *height = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterH(height);
    QImage *orangeMask = new QImage(280, 140, QImage::Format_RGB32);
    QPainter painterOM(orangeMask);

    QString mainLbl1 = gen_random_main_label1();
    QString mainLbl2 = gen_random_main_label2();
    QString smallLbl = gen_random_small_str(6, 12);

    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);

    // Diffuse
    QImage back(":/pictures/MyFLORIDA_small.png");
    painterD.drawImage(QPoint(0, 0), back);

    drawText(painterD, font, QColor(17, 141, 128), mainLbl1, mainLbl2, smallLbl);

    // Height
    painterH.setPen(Qt::black);
    painterH.setBrush(Qt::black);
    painterH.drawRect(height->rect());

    drawText(painterH, font, Qt::white, mainLbl1, mainLbl2, smallLbl);

    // Orange mask
    QImage backOM(":/pictures/OrangeMask_small.png");
    painterOM.drawImage(QPoint(0, 0), backOM);

    drawText(painterOM, font, Qt::black, mainLbl1, mainLbl2, smallLbl);

    QImage* height_b = gaussBlur(height, 2);

    QImage *normal = height2Normal(height_b);
    painterH.end();
    delete height;
//    delete height_b;
    emit heightGenerated(height_b);
    emit diffuseGenerated(diffuse);
    emit normalGenerated(normal);
    emit orangeMaskGenerated(orangeMask);
}
