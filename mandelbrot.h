#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "mandelbrot/include/Mandelbrot.h"

#include <QImage>

class Mandelbrot {
public:
    Mandelbrot(int w, int h);
    void setCenter(int x, int y);
    void zoomIn();
    void zoomOut();
    void zoomOriginal();
    QImage createFractalImage();

private:
    int width{0};
    int height{0};
    mandelbrot::Mandelbrot mandelbrot;
};

#endif // MANDELBROT_H
