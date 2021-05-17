#ifndef __STAR_H
#define __STAR_H

#include<SDL2/SDL.h>
#include<string>

class Star{
	public:
		Star(std::string name, std::string c, double a, double d, double mag, double ly, double ma, double md):
			name(name), constellation(c),
			right_ascension_2017(a), declination_2017(d), magnitude(mag), light_years(ly),
			motion_right_ascension(ma), motion_declination(md), display(0)
		{

		}
		int setMap(double latitude, double radius, double cx, double cy);
		int setPrecession(double year, double latitude);
		int over(int _x, int _y);
		double getMotionRightAscension()
		{
			return motion_right_ascension;
		}
		double getMotionDeclination()
		{
			return motion_declination;
		}
		double getRightAscension()
		{
			return right_ascension;
		}
		double getDeclination()
		{
			return declination;
		}
		void setRightAscension(double r)
		{
			right_ascension = r;
		}
		void setDeclination(double d)
		{
			declination = d;
		}
		double getRightAscension2017()
		{
			return right_ascension_2017;
		}
		double getDeclination2017()
		{
			return declination_2017;
		}
		double getMagnitude()
		{
			return magnitude;
		}
		double getMagnitudeMap()
		{
			return magnitude_map;
		}
		int getLightYears()
		{
			return light_years;
		}
		double getX()
		{
			return x;
		}
		double getY()
		{
			return y;
		}
		void setOver(int x, int y)
		{
			xover = x;
			yover = y;
		}

		std::string getName()
		{
			return name;
		}
		void setDisplay(int d)
		{
			display = d;
		}

		int getDisplay()
		{
			return display;
		}

		std::string getConstellation()
		{
			return constellation;
		}

	private:
		double right_ascension_2017, declination_2017, magnitude, motion_right_ascension, motion_declination;
		double right_ascension, declination, magnitude_map, x, y;
		int light_years, xover, yover, display;
		std::string name, constellation;
};

#endif
