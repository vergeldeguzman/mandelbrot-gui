#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "zoom.h"

#include <QObject>
#include <QImage>
#include <QString>

#include <utility>

const int MAX_ITERATIONS = 1024;

struct IterationRange
{
    int startRange;
    int endRange;
    QRgb startColor;
    QRgb endColor;
    int iterations;
};

class Mandelbrot : public QObject
{
    Q_OBJECT

public:
    explicit Mandelbrot(QObject *parent, int w, int h);
    void setCenter(int x, int y)
    {
        zoom.setCenter(x, y);
    }
    void zoomIn();
    void zoomOut();
    void zoomOriginal();
    QImage createFractalImage();

signals:
    void notifyProgress(int);
    void notifyStatusMessage(const QString);
    void clearStatusMessage();

private:
    int width{0};
    int height{0};
    Zoom zoom;
    std::vector<std::pair<double, QRgb> > colorRanges;

    int getIterations(double x, double y);
    std::vector<IterationRange> createIterationRanges(const std::vector<int>& histogram);
    std::vector<int> createHistogram(const std::vector<std::vector<int> >& fractals);
    std::vector<std::vector<int> > createFractal();
    QImage toImage(const std::vector<std::vector<int> >& fractals,
                   const std::vector<int>& histogram,
                   const std::vector<IterationRange>& iterationRanges);
};



#endif // MANDELBROT_H
