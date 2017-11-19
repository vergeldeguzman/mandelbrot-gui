#include "mandelbrot.h"
#include "mandelbrot/include/Rgb.h"
#include "mandelbrot/include/Zoom.h"

Mandelbrot::Mandelbrot(int w, int h) :
    width(w),
    height(h),
    mandelbrot(width, height)
{
    mandelbrot.addColorRange(make_pair(0.0, mandelbrot::Rgb{.red=0x00,.green=0x00,.blue=0xff}));
    mandelbrot.addColorRange(make_pair(0.05, mandelbrot::Rgb{.red=0xff,.green=0x00,.blue=0x00}));
    mandelbrot.addColorRange(make_pair(0.08, mandelbrot::Rgb{.red=0xff,.green=0xff,.blue=0x00}));
    mandelbrot.addColorRange(make_pair(1.0, mandelbrot::Rgb{.red=0xff,.green=0xff,.blue=0xff}));

    zoomOriginal();
}

void Mandelbrot::setCenter(int x, int y)
{
    mandelbrot.setCenter(x, y);
    mandelbrot.setScale(1.0);
}

void Mandelbrot::zoomOut()
{
    mandelbrot.setCenter(width/2, height/2);
    mandelbrot.setScale(1/0.5);
}

void Mandelbrot::zoomIn()
{
    mandelbrot.setCenter(width/2, height/2);
    mandelbrot.setScale(0.5);
}

void Mandelbrot::zoomOriginal()
{
    mandelbrot.resetCenter();
    mandelbrot.setScale(0.005);
}

QImage Mandelbrot::createFractalImage() {
    vector<vector<mandelbrot::Rgb> > fractalImage = mandelbrot.createFractalImage();

    QImage image(width, height, QImage::Format_RGB32);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            mandelbrot::Rgb rgb = fractalImage[x][y];
            image.setPixel(x, y, qRgb(rgb.red, rgb.green, rgb.blue));
        }
    }
    return image;
}
