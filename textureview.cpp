#include "textureview.h"

TextureView::TextureView(QWidget *parent)
    : QWidget (parent)
{
    labelD = new QLabel(this);
    labelD->setGeometry(QRect(0, 0, 280, 140));
    labelH = new QLabel(this);
    labelH->setGeometry(QRect(0, 0, 280, 140));
    labelN = new QLabel(this);
    labelN->setGeometry(QRect(0, 0, 280, 140));

    resize(200, 200);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setMargin(25);
    vLayout->addWidget(labelD);
    vLayout->addWidget(labelH);
    vLayout->addWidget(labelN);
}

void TextureView::setImageD(QImage *img)
{
    labelD->setPixmap(QPixmap::fromImage(*img));
}

void TextureView::setImageH(QImage *img)
{
    labelH->setPixmap(QPixmap::fromImage(*img));
}

void TextureView::setImageN(QImage *img)
{
    labelN->setPixmap(QPixmap::fromImage(*img));
}
