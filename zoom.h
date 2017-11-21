#ifndef ZOOM_H
#define ZOOM_H

#include <utility>

class Zoom
{
private:
	int width{0};
	int height{0};
	double centerX{0.0};
	double centerY{0.0};
    double scaleFactor{1.0};

public:
    Zoom(int width, int height) :
        width(width),
        height(height)
    {
    }

    void setScaleFactor(double _scaleFactor)
    {
        scaleFactor *= _scaleFactor;
	}

    void resetCenter()
    {
		centerX = 0.0;
		centerY = 0.0;
        scaleFactor = 1.0;
	}
	void setCenter(int x, int y);
	std::pair<double, double> scaleCoords(int x, int y) const;
};

#endif // ZOOM_H
