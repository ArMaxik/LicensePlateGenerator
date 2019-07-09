#ifndef TEXTUREVIEW_H
#define TEXTUREVIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class TextureView : public QWidget
{
    Q_OBJECT
public:
    TextureView(QWidget *parent = nullptr);

public slots:
    void setImageD(QImage *img);
    void setImageH(QImage *img);
    void setImageN(QImage *img);

private:
    QLabel *labelD;
    QLabel *labelH;
    QLabel *labelN;
};

#endif // TEXTUREVIEW_H
