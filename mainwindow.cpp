#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mouseeventfilter.h"

#include <QColor>
#include <QEvent>
#include <QKeyEvent>
#include <QProgressBar>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mandelbrot(this, 800, 600)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(mandelbrot.createFractalImage()));
    ui->label->adjustSize();
    ui->label->installEventFilter(this);

    connect(&mandelbrot, SIGNAL(notifyStatusMessage(const QString)), ui->statusBar, SLOT(showMessage(const QString)));
    connect(&mandelbrot, SIGNAL(clearStatusMessage()), ui->statusBar, SLOT(clearMessage()));

    QProgressBar* progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    ui->statusBar->addPermanentWidget(progressBar);
    connect(&mandelbrot, SIGNAL(notifyProgress(int)), progressBar, SLOT(setValue(int)));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        int x = mouseEvent->x();
        int y = mouseEvent->y();
        mandelbrot.setCenter(x, y);
        ui->label->setPixmap(QPixmap::fromImage(mandelbrot.createFractalImage()));
        return true;
    }

    return QObject::eventFilter(obj, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionZoom_In_triggered()
{
    mandelbrot.zoomIn();
    ui->label->setPixmap(QPixmap::fromImage(mandelbrot.createFractalImage()));
}

void MainWindow::on_actionZoom_Out_triggered()
{
    mandelbrot.zoomOut();
    ui->label->setPixmap(QPixmap::fromImage(mandelbrot.createFractalImage()));
}

void MainWindow::on_actionZoom_Original_triggered()
{
    mandelbrot.zoomOriginal();
    ui->label->setPixmap(QPixmap::fromImage(mandelbrot.createFractalImage()));
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                                "Untitled.png",
                                "Images (*.png *.bmp *.jpg)");
    QImage image = ui->label->pixmap()->toImage();
    image.save(fileName);
}
