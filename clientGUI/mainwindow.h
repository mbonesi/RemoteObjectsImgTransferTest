#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../DataConsumer/imageclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ImageClient *_pClient = nullptr;

public:
    MainWindow(QSharedPointer<ImageProviderReplica> ptr, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onFPSUpdated(int FPS);
    void onNewImageAvailable(QImage img);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_spinBoxTimeIntervalMs_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
