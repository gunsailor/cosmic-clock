#ifndef __STARS_UTILS_
#define __STARS_UTILS_

#include<SDL2/SDL.h>
#include<algorithm>
#include<list>
#include"Star.h"
#include"Quaternion.h"
#include"Complex.h"

class StarsUtils{
	public:
		StarsUtils();
		int loadStars();
		void deleteStars(void *s);
		int setPrecession(Star *s, double year, double lat, double J2000);
		int drawStars(SDL_Renderer *renderer, double year, double phi, int update, int update_latitude, double lat, double J2000);
		int drawCirclesMap(SDL_Renderer *renderer, double phi, double lat, Media *text, SDL_Color redColor);
		void setLatitude(double l);
		int processField(SDL_Renderer *renderer, double angle, double phi, int ecliptic);
		std::list<Star*> getStars()
		{
			return stars;
		}
	private:
		std::list<Star*> stars;
		double radius;
		double tropic_year, sideral_year, anomalistic_year, latitude;
		double cycle_precession;
		double cycle_perihelion;
		double perihelion_motion_year, precession_motion_year;
		double right_ascension_axis, declination_axis, highest_obliquity, lowest_obliquity, obliquity_radius;
};

#endif


