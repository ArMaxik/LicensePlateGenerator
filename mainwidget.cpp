#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QFileDialog>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , lpm(new LicensePlateManager)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayoutMain);

    ui->savePath->setText(QDir::currentPath() + "/");

    QObject::connect(lpm, &LicensePlateManager::imageGenerated, ui->progressBar, &QProgressBar::setValue);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete lpm;
}

void MainWidget::on_pushButton_clicked()
{
    ui->progressBar->setMaximum(ui->numberOfRendering->value());
    ui->progressBar->setValue(0);
    lpm->generate(ui->numberOfRendering->value(), ui->savePath->text() + ui->saveFileName->text());
}

void MainWidget::on_buttonChoseSavePath_clicked()
{
    ui->savePath->setText(
                QFileDialog::getExistingDirectory(
                           this
                         , "Save path"
                         , ""
                         , QFileDialog::ShowDirsOnly
                         | QFileDialog::DontResolveSymlinks) + "/");
}
