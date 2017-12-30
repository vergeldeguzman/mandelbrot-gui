#include "mandelbrot.h"

#include <complex>

using namespace std;

Mandelbrot::Mandelbrot(QObject *parent, int w, int h) :
    QObject(parent),
    width(w),
    height(h),
    zoom(width, height)
{
    colorRanges.push_back(make_pair(0.0,  qRgb(0x00, 0x00, 0xff)));
    colorRanges.push_back(make_pair(0.05, qRgb(0xff, 0x00, 0x00)));
    colorRanges.push_back(make_pair(0.08, qRgb(0xff, 0xff, 0x00)));
    colorRanges.push_back(make_pair(1.0,  qRgb(0xff, 0xff, 0xff)));

    zoomOriginal();
}

void Mandelbrot::zoomOut()
{
    zoom.setCenter(width/2, height/2);
    zoom.setScaleFactor(1/0.5);
}

void Mandelbrot::zoomIn()
{
    zoom.setCenter(width/2, height/2);
    zoom.setScaleFactor(0.5);
}

void Mandelbrot::zoomOriginal()
{
    zoom.resetCenter();
    zoom.setScaleFactor(0.005);
}

int Mandelbrot::getIterations(double x, double y) {
    complex<double> z = 0;
    complex<double> c(x, y);

    int iterations = 0;
    while (iterations < MAX_ITERATIONS) {
        // f(z) = z*z + c
        z = z*z + c;
        if (abs(z) > 2) {
            break;
        }

        iterations++;
    }

    return iterations;
}

vector<vector<int> > Mandelbrot::createFractal() {
    emit notifyProgress(0);

    vector<vector<int> > fractals;
    fractals.reserve(width);
    int dimension = width*height;
    for (int x = 0; x < width; x++) {
        fractals.push_back(vector<int>());
        fractals.back().reserve(height);
        for (int y = 0; y < height; y++) {
            pair<double, double> newCoords = zoom.scaleCoords(x, y);
            fractals.back().push_back(getIterations(newCoords.first, newCoords.second));
            emit notifyProgress(100*(x*height + y + 1)/dimension);
        }
    }
    return fractals;
}

QImage Mandelbrot::toImage(const vector<vector<int> >& fractals,
        const vector<int>& histogram,
        const vector<IterationRange>& iterationRanges) {
    emit notifyProgress(0);

    int dimension = width*height;
    QImage image(width, height, QImage::Format_RGB32);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int iterations = fractals[x][y];

            auto colorIter = find_if(iterationRanges.begin(), iterationRanges.end(),
                [&iterations](const IterationRange& iterationRange){
                    return (iterationRange.startRange <= iterations && iterationRange.endRange > iterations);
                }
            );

            int red = 0;
            int green = 0;
            int blue = 0;
            if (iterations != MAX_ITERATIONS && colorIter != iterationRanges.end()) {
                int pixels = 0;
                for (int i = colorIter->startRange; i <= iterations; ++i) {
                    pixels += histogram[i];
                }
                double pixelPerc = static_cast<double>(pixels)/colorIter->iterations;
                int redDiff = qRed(colorIter->endColor) - qRed(colorIter->startColor);
                int greenDiff = qGreen(colorIter->endColor) - qGreen(colorIter->startColor);
                int blueDiff = qBlue(colorIter->endColor) - qBlue(colorIter->startColor);

                red = qRed(colorIter->startColor) + (redDiff*pixelPerc);
                green = qGreen(colorIter->startColor) + (greenDiff*pixelPerc);
                blue = qBlue(colorIter->startColor) + (blueDiff*pixelPerc);
            }
            image.setPixel(x, y, qRgb(red, green, blue));
            emit notifyProgress(100*(x*height + y + 1)/dimension);
        }
    }
    return image;
}

vector<int> Mandelbrot::createHistogram(const vector<vector<int> >& fractals) {
    emit notifyProgress(0);

    int dimension = width*height;
    vector<int> histogram(MAX_ITERATIONS, 0);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int iterations = fractals[x][y];
            if (iterations != MAX_ITERATIONS) {
                histogram[iterations]++;
            }
            emit notifyProgress(100*(x*height + y + 1)/dimension);
        }
    }
    return histogram;
}

vector<IterationRange> Mandelbrot::createIterationRanges(const vector<int>& histogram) {
    vector<IterationRange> iterationRanges;
    int startRange = static_cast<int>(colorRanges[0].first*MAX_ITERATIONS);
    QRgb startColor = colorRanges[0].second;

    for_each(colorRanges.begin() + 1, colorRanges.end(),
        [&histogram, &startRange, &startColor, &iterationRanges](const pair<double, QRgb>& colorRange){
            int endRange = static_cast<int>(colorRange.first*MAX_ITERATIONS);
            QRgb endColor = colorRange.second;
            int iterationRange = 0;
            for (int i = startRange; i < endRange; ++i) {
                iterationRange += histogram[i];
            }
            iterationRanges.push_back(
                IterationRange{
                    startRange,
                    endRange,
                    startColor,
                    endColor,
                    iterationRange});

            startRange = endRange;
            startColor = endColor;
        }
    );
    return iterationRanges;
}

QImage Mandelbrot::createFractalImage() {
    emit notifyStatusMessage("Calculating mandelbrot iterations");
    vector<vector<int> > fractals = createFractal();

    emit notifyStatusMessage("Creating histogram");
    vector<int> histogram = createHistogram(fractals);

    emit notifyStatusMessage("Creating iteration color ranges");
    vector<IterationRange> iterationRanges = createIterationRanges(histogram);

    emit notifyStatusMessage("Creating fractal image");
    QImage image = toImage(fractals, histogram, iterationRanges);

    emit clearStatusMessage();
    return image;
}
