#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QSharedPointer<ImageProviderReplica> ptr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)    
{
    ui->setupUi(this);
    _pClient = new ImageClient(ptr);
    connect(_pClient, SIGNAL(receivedRateUpdate(int)), this, SLOT(onFPSUpdated(int)));
    connect(_pClient, SIGNAL(newImageAvailable(QImage)), this, SLOT(onNewImageAvailable(QImage)));
}

MainWindow::~MainWindow()
{
    delete _pClient;
    delete ui;
}

void MainWindow::onFPSUpdated(int FPS)
{
    statusBar()->showMessage(QString("FPS=%1").arg(FPS));
    qDebug() << "FPS= " << FPS;
}

void MainWindow::onNewImageAvailable(QImage img)
{
    QPixmap pixmap = QPixmap::fromImage(img);
    int scaleFactor = 4;
    ui->labelImage->setPixmap(pixmap.scaled(
                             pixmap.width()/scaleFactor,
                             pixmap.height()/scaleFactor,
                             Qt::KeepAspectRatio));
    ui->labelImage->show();
}


void MainWindow::on_pushButtonStart_clicked()
{
    _pClient->Start(ui->spinBoxTimeIntervalMs->value());
}

void MainWindow::on_pushButtonStop_clicked()
{
    _pClient->Stop();
}

void MainWindow::on_spinBoxTimeIntervalMs_valueChanged(int arg1)
{
    _pClient->SetRequestsPeriod(arg1);
}
