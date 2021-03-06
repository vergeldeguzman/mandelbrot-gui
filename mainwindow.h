#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

#include "mandelbrot.h"

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionZoom_Original_triggered();

    void on_actionSave_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    Mandelbrot mandelbrot;

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAINWINDOW_H
