#include<fstream>
#include<SDL2/SDL.h>
#include"SDL2_gfxPrimitives.h"
#include"Star.h"
#include"Quaternion.h"
#include"Complex.h"
#include"Media.h"
extern "C"{
#include"cJSON.h"
}
#include"StarsUtils.h"

StarsUtils::StarsUtils():tropic_year(365.2421897916L),sideral_year(365.256363004L),anomalistic_year(365.259635864L),
		highest_obliquity(24.5044L),lowest_obliquity(22.0425L), right_ascension_axis(0.0L), declination_axis(0.0L)
{
	cycle_precession = tropic_year / (sideral_year - tropic_year);
	cycle_perihelion = tropic_year / (anomalistic_year - sideral_year);
	perihelion_motion_year = 2.0L * M_PI / cycle_perihelion;
	precession_motion_year = 2.0L * M_PI / cycle_precession;
}

int StarsUtils::setPrecession(Star *s, double year, double lat, double J2000)
{
	int ok = 0;

	double right_ascension = - s->getRightAscension2017() * M_PI / 12.0L;
	double declination = s->getDeclination2017() * M_PI / 180.0L;

	obliquity_radius = - 2.0L * M_PI / 41000.0L * (year - 2885.0L);
	declination_axis = ((highest_obliquity + lowest_obliquity) / 2.0L + 
			(highest_obliquity - lowest_obliquity) / 2.0L  * (double)(sinl((double)(obliquity_radius)))) * M_PI / 180.0L;
	if(J2000 < 0.0L)
	{
		right_ascension -= s->getMotionRightAscension() / 1000.0L / 3600.0L * (year - 2000.0L) * M_PI / 12.0L;
		declination += s->getMotionDeclination() / 1000.0L / 3600.0L * (year - 2000.0L) * M_PI / 180.0L;
		
		right_ascension_axis = precession_motion_year * (year - 2000.0L);
		
		Quaternion q(right_ascension, declination);

		q.polar2cartesian();

		q.create_rotate_vector(0.0L, (23.0L + 26.0L / 60.0L + 21.406L / 3600.0L) * M_PI / 180.0L, 1);

		q.rotate();

		q.create_rotate_vector(M_PI / 2.0L, -right_ascension_axis, 0);

		q.rotate();
		
		q.create_rotate_vector(M_PI, declination_axis, 1);

		q.rotate();

		q.cartesian2polar(1);

		right_ascension = q.getRightAscension();
		declination = q.getDeclination();
	}
	

	if(lat * right_ascension < 0)
		s->setRightAscension(- lat * right_ascension);
	else if(lat * right_ascension > 0)
		s->setRightAscension(2.0L * M_PI - lat * right_ascension);

	double dec = declination * lat;
	s->setDeclination(dec);

	if((double)(acosl(cosl(latitude)*cosl(dec)+sinl(latitude)*sinl(dec))) < M_PI / 2.0L)
		ok = 1;

	return ok;
}

int StarsUtils::drawStars(SDL_Renderer *renderer, double year, double phi, int update, int update_latitude, double lat, double J2000)
{
	for(auto it = stars.begin(); it != stars.end(); ++it)
	{
		if(update || update_latitude)
		{
			if(setPrecession((*it), year, lat, J2000))
			{
				(*it)->setMap(latitude, radius, 768 / 2, 768 / 2);
				(*it)->setDisplay(1);
			}else{
				(*it)->setDisplay(0);
				(*it)->setOver(-10, -10);
			}
		}
		if((*it)->getDisplay())
		{
			double magnitude = (*it)->getMagnitudeMap();
			Complex star((*it)->getX(), (*it)->getY()), center(768.0L / 2.0L, 768.0L / 2.0L);
			star.rotate(center, -phi - M_PI / 2.0L);
			filledEllipseColor(renderer, star.getPosX(), star.getPosY(), magnitude, magnitude, 0xFFFFFFFF);
			(*it)->setOver(star.getPosX(), star.getPosY());
		}
	}
	return EXIT_SUCCESS;
}

int StarsUtils::loadStars()
{
	std::string line, file;
	std::ifstream f("stars.json");
	if(!f)
	{
		fprintf(stderr, "No such file stars.json... Must be provided!!\n");
		return EXIT_FAILURE;
	}
	while(getline(f, line))
	{
		file += line;
	}
	cJSON *root = cJSON_Parse(file.c_str());
	cJSON *constellations = cJSON_GetObjectItem(root, "constellation");
	while(constellations != NULL)
	{
		char *constellation = cJSON_GetObjectItem(constellations, "name")->valuestring;
		cJSON *star = cJSON_GetObjectItem(constellations, "star");
		while(star!= NULL)
		{
			char *name = cJSON_GetObjectItem(star, "name")->valuestring;
			double ra_medium = cJSON_GetObjectItem(star, "RA")->valuedouble;
			double dec_medium = cJSON_GetObjectItem(star, "DEC")->valuedouble;
			double mag = cJSON_GetObjectItem(star, "MAG")->valuedouble;
			double ma = cJSON_GetObjectItem(star, "mRA")->valuedouble;
			double mdec = cJSON_GetObjectItem(star, "mDEC")->valuedouble;
			int al = cJSON_GetObjectItem(star, "AL")->valueint;
			Star *s = new Star(name, constellation, ra_medium, dec_medium, mag, al, ma, mdec);
			stars.push_back(s);
			star = star->next;
		}
		constellations = constellations->next;
	}
	cJSON_Delete(root);
	return EXIT_SUCCESS;
}

void StarsUtils::setLatitude(double l)
{
	latitude = l;
	radius = 350.0L / tanl(M_PI / 4 - (latitude - M_PI / 2.0L) / 2.0L);
}
int StarsUtils::drawCirclesMap(SDL_Renderer *renderer, double phi, double lat, Media *text, SDL_Color redColor)
{
	circleColor(renderer, 768 / 2, 768 / 2, radius, 0xFF0000FF);
	processField(renderer, -(M_PI / 2.0L - latitude), 0.0L, 0);
	processField(renderer, -lat * declination_axis, phi, 1);
	processField(renderer, latitude, 0.0L, 2);
	if(lat > 0.0L)
	{
		text->loadText(renderer, "E", redColor);
		text->render(renderer, 768 / 2 - radius-10 ,768 / 2 -25);
		text->loadText(renderer, "W", redColor);
		text->render(renderer, 768 / 2 + radius ,768 / 2 -25);	
	}else{
		text->loadText(renderer, "W", redColor);
		text->render(renderer, 768 / 2 - radius-10 ,768 / 2 -25);
		text->loadText(renderer, "E", redColor);
		text->render(renderer, 768 / 2 + radius ,768 / 2 -25);	
	}

	return EXIT_SUCCESS;
}

int StarsUtils::processField(SDL_Renderer *renderer, double angle, double phi, int circle)
{
	double vec[4], end = M_PI;
	if(circle != 2)
		end *= 2.0L;
	for(double i = 0.0L; i < end; i += 0.005L)
	{
		Quaternion q(i, 0.0L, radius);
		q.create_rotate_vector(0.0L, angle, 1);
		q.rotate();
		q.getVector(vec);
		q.cartesian2polar(1);
		double t = radius / (vec[3] + radius);
		if(circle == 1){
			Complex c = Complex(vec[1] * t + 768 / 2, vec[2] * t + 768 / 2);
			Complex c1 = Complex(768.0L / 2.0L, 768.0L / 2.0L);
            		c.rotate(c1, - phi + M_PI / 2.0L);
			
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawPoint(renderer, c.getPosX(), c.getPosY());
		}else if(!circle){
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
			SDL_RenderDrawPoint(renderer, vec[1] * t + 768 / 2, vec[2] * t + 768 / 2);
		}else{
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
			SDL_RenderDrawPoint(renderer, vec[1] * t + 768 / 2, vec[2] * t + 768 / 2);
		}
	}

	return EXIT_SUCCESS;
}
