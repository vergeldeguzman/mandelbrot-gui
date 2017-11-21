#include "zoom.h"

using namespace std;

void Zoom::setCenter(int x, int y)
{
    centerX += (x - width/2)*scaleFactor;
    centerY += (y - height/2)*scaleFactor;
}

pair<double, double> Zoom::scaleCoords(int x, int y) const
{
    double rescaledX = (x - width/2)*scaleFactor + centerX;
    double rescaledY = (y - height/2)*scaleFactor + centerY;
	return make_pair(rescaledX, rescaledY);
}
