#include<iostream>
#include "Quaternion.h"
#include"Star.h"
#include"Complex.h"
extern "C"{
	#include"math.h"
}

int Star::setMap(double latitude, double radius, double cx, double cy)
{
	magnitude_map = exp(-magnitude*log(1.4L)) * 5.0L;
	double r = radius * tanl(M_PI / 4.0L - declination / 2.0L);
	Complex c(right_ascension, r, false);
	x = c.getPosX() + cx;
	y = c.getPosY() + cy;

	return EXIT_SUCCESS;
}

int Star::over(int _x, int _y)
{
	int over = 0;
	if(sqrt(pow(xover - _x, 2) + pow(yover - _y, 2)) <= magnitude_map)
		over = 1;
	return over;
}
