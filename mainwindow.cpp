#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mouseeventfilter.h"

#include <QColor>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mandelbrot(800, 600)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(mandelbrot.createFractalImage()));
    ui->label->adjustSize();
    qDebug("Label: (%d,%d)", ui->label->width(),  ui->label->height());
    qDebug("Pixmap: (%d,%d)", ui->label->pixmap()->width(),  ui->label->pixmap()->height());
    ui->label->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    qDebug("Label: (%d,%d)", ui->label->width(),  ui->label->height());
    qDebug("Pixmap: (%d,%d)", ui->label->pixmap()->width(),  ui->label->pixmap()->height());

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
