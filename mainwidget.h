#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "licenseplatemanager.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_clicked();

    void on_buttonChoseSavePath_clicked();

private:
    Ui::MainWidget *ui;
    LicensePlateManager *lpm;
};

#endif // MAINWIDGET_H