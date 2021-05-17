#include<iostream>
#include<string>
#include<cmath>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include"cJSON.h"
#include"Complex.h"
#include"Button.h"
#include"StarsUtils.h"
#include <ctime>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


bool init(SDL_Window** window, SDL_Renderer** renderer);
SDL_Texture* loadTexture(SDL_Renderer* renderer, int width, int height);
int display_stars_features(SDL_Renderer *renderer, StarsUtils *utils, Media *text,int x , int y, SDL_Color redColor, double lat);
int draw_map(SDL_Renderer *screen, Media *text, SDL_Color blackColor, SDL_Color redColor, double theta, double lat);
int draw_controls(SDL_Renderer *renderer, Media *text, SDL_Color redColor, std::list<Button*> buttons, int hours, int minutes, int days, int months, int years, int latitudes);

int main(int argc, char *argv[])
{
	int latitude = 43;
       	double lat = 1.0L, j2000 = 1.0L;
	SDL_Texture *gTexture = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	time_t now = time(0);
	tm *gmtm = localtime(&now);	
	init(&window, &renderer);
	StarsUtils utils;
	utils.setLatitude(static_cast<double>(latitude)*M_PI/180.0L);
	if(utils.loadStars() != EXIT_SUCCESS)
		return EXIT_FAILURE;
	Media text;
	text.loadTTF("Marlboro.ttf", 20);
	SDL_Event event;
	SDL_Color blackColor = {0, 0, 0, 255};
	SDL_Color redColor = {255, 0, 0, 255};
	int play = 1;
	int x, y;
	double theta = 0;
	int m[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int hours = 0, minutes = 0, days = gmtm->tm_mday + 1, months = gmtm->tm_mon + 1, years = 1900 + gmtm->tm_year;
	std::list<Button*> buttons;
	Button* up_hours = new Button(renderer, "up.png", 0, 23);
	Button* down_hours = new Button(renderer, "down.png", 0, 23);
	Button* up_min = new Button(renderer, "up.png", 0, 59);
	Button* down_min = new Button(renderer, "down.png", 0, 59);
	Button* up_day = new Button(renderer, "up.png", 1, 30);
	Button* down_day = new Button(renderer, "down.png", 1, 30);
	Button* up_month = new Button(renderer, "up.png", 1, 12);
	Button* down_month = new Button(renderer, "down.png", 1, 12);
	Button* up_year = new Button(renderer, "up.png", 2017, 25788);
	Button* down_year = new Button(renderer, "down.png", 2017, 25788);
	Button* up_year_10 = new Button(renderer, "up.png", 2017, 25788);
	Button* down_year_10 = new Button(renderer, "down.png", 2017, 25788);
	Button* up_year_100 = new Button(renderer, "up.png", 2017, 25788);
	Button* down_year_100 = new Button(renderer, "down.png", 2017, 25788);
	Button* up_year_1000 = new Button(renderer, "up.png", 2017, 25788);
	Button* down_year_1000 = new Button(renderer, "down.png", 2017, 25788);
	Button* up_latitude = new Button(renderer, "up.png", 35, 70);
	Button* down_latitude = new Button(renderer, "down.png", 35, 70);
	Button* hemisphere = new Button(renderer, "nord.png", "sud.png");
	Button* J2000 = new Button(renderer, "checked.png", "unchecked.png");
	J2000->setRect(50, 25, 25, 25);
	up_hours->setRect(50, 75, 25, 25);
	down_hours->setRect(50, 125, 25, 25);
	up_min->setRect(130, 75, 25, 25);
	down_min->setRect(130, 125, 25, 25);
	up_day->setRect(50, 175, 25, 25);
	down_day->setRect(50, 225, 25, 25);
	up_month->setRect(50, 275, 25, 25);
	down_month->setRect(50, 325, 25, 25);
	up_year->setRect(50, 375, 25, 25);
	down_year->setRect(50, 425, 25, 25);
	up_year_10->setRect(75, 375, 25, 25);
	down_year_10->setRect(75, 425, 25, 25);
	up_year_100->setRect(100, 375, 25, 25);
	down_year_100->setRect(100, 425, 25, 25);
	up_year_1000->setRect(125, 375, 25, 25);
	down_year_1000->setRect(125, 425, 25, 25);
	up_latitude->setRect(50, 475, 25, 25);
	down_latitude->setRect(50, 525, 25, 25);
	hemisphere->setRect(150, 500, 25, 25);
	buttons.push_back(up_hours);
	buttons.push_back(down_hours);
	buttons.push_back(up_min);
	buttons.push_back(down_min);
	buttons.push_back(up_day);
	buttons.push_back(down_day);
	buttons.push_back(up_month);
	buttons.push_back(down_month);
	buttons.push_back(up_year_10);
	buttons.push_back(down_year_10);
	buttons.push_back(up_year_100);
	buttons.push_back(down_year_100);
	buttons.push_back(up_year_1000);
	buttons.push_back(down_year_1000);
	buttons.push_back(up_year);
	buttons.push_back(down_year);
	buttons.push_back(up_latitude);
	buttons.push_back(down_latitude);
	buttons.push_back(hemisphere);
	buttons.push_back(J2000);

	gTexture = loadTexture(renderer, 768, 768);
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		return EXIT_FAILURE;
	}

	int update = 1;
	int update_latitude = 0;
	while (play)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		    case SDL_QUIT:
			play = 0;
			break;
		    case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
				break;
			    	case SDLK_RETURN:
				break;
			}
			break;
			case SDL_MOUSEBUTTONUP:
				up_hours->action(&hours, 1, x - 768, y);
				down_hours->action(&hours, -1, x - 768, y);
				up_min->action(&minutes, 5, x - 768, y);
				down_min->action(&minutes, -5, x - 768, y);
				up_day->action(&days, 1, x - 768, y);
				down_day->action(&days, -1, x - 768, y);
				up_month->action(&months, 1, x - 768, y);
				down_month->action(&months, -1, x - 768, y);
				up_year->action(&years, 1, x - 768, y, &update);
				down_year->action(&years, -1, x - 768, y, &update);
				up_year_10->action(&years, 10, x - 768, y, &update);
				down_year_10->action(&years, -10, x - 768, y, &update);
				up_year_100->action(&years, 100, x - 768, y, &update);
				down_year_100->action(&years, -100, x - 768, y, &update);
				up_year_1000->action(&years, 1000, x - 768, y, &update);
				down_year_1000->action(&years, -1000, x - 768, y, &update);
				up_latitude->action(&latitude, 1, x - 768, y, &update_latitude);
				down_latitude->action(&latitude, -1, x - 768, y, &update_latitude);
				hemisphere->action(renderer, &lat, x - 768, y, &update);
				J2000->action(renderer, &j2000, x - 768, y, &update);
				if(update_latitude)
					utils.setLatitude(static_cast<double>(latitude)*M_PI/180.0L);
				break;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
			break;

		}

		theta = days;
		for(int i = 0; i < months; i++)
			theta += m[i];
		theta = theta * 2.0L * M_PI / 365.0L;
		theta += (hours / 12.0L + minutes / ( 12.0L * 60.0L)) * M_PI - 1.910776902L;
		if(lat < 0.0L)
			theta = - theta;
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

		SDL_RenderClear( renderer );

		SDL_Rect viewport;
		viewport.x = 0;
		viewport.y = 0;
		viewport.w =  768;
		viewport.h = 768;
		SDL_RenderSetViewport( renderer, &viewport );
		SDL_RenderCopy( renderer, gTexture, NULL, NULL );
		
		filledEllipseColor(renderer, 384, 384, 384, 384, 0xFFFFFFFF);
		draw_map(renderer, &text, blackColor, redColor, theta, lat);
		filledEllipseColor(renderer, 384, 384, 350, 350, 0xFF000000);
		utils.drawStars(renderer, static_cast<double>(years), theta, update, update_latitude, lat, j2000);
		utils.drawCirclesMap(renderer, theta, lat, &text, redColor);

		viewport.x = 768;
		viewport.y = 0;
		viewport.w =  256;
		viewport.h = 768;
		SDL_RenderSetViewport( renderer, &viewport );
		SDL_RenderCopy( renderer, gTexture, NULL, NULL );
		draw_controls(renderer, &text, redColor, buttons, hours, minutes, days, months, years, latitude);
		display_stars_features(renderer, &utils, &text, x, y, redColor, lat);
		SDL_RenderPresent( renderer );
		if(update)
			update = 0;
		if(update_latitude)
			update_latitude = 0;
    }
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;	
	SDL_DestroyRenderer( renderer );
	renderer = NULL;
	SDL_DestroyWindow( window );
	window = NULL;
    	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

    return EXIT_SUCCESS;
}


bool init(SDL_Window ** window, SDL_Renderer **renderer)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		*window = SDL_CreateWindow( "stars shift", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			*renderer = SDL_CreateRenderer( *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( *renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, int width, int height)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);;
	if( loadedSurface == NULL )
	{
		printf( "Unable to create surface! SDL_image Error: %s\n", SDL_GetError() );
	}else{
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture! SDL Error: %s\n", SDL_GetError() );
		}
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}


int draw_map(SDL_Renderer *renderer, Media *text, SDL_Color blackColor, SDL_Color redColor, double theta, double lat)
{
	SDL_Rect position;
	std::string right_ascension;
	char tmp[3];
	int j = 0, k = 0;
	for(double i = 0; i < M_PI; i+=0.021816616L)
	{
		Complex c, c1, c2, c3, c4, c5, c6;
		c = Complex(768.0L / 2.0L, 768.0L / 2.0L);
		c1 = Complex(768.0L / 2.0L, 740.0L);
		c2 = Complex(768.0L, 768.0L / 2.0L);
		c3 = Complex(768.0L, 768.0L / 2.0L);
		c2.rotate(c, -(i + theta));
		c3.rotate(c, -(i + M_PI + theta));
		c4 = Complex(c2.getPosX(), c2.getPosY());
		c5 = Complex(c3.getPosX(), c3.getPosY());
		if(!(j % 6))
		{
			if(!(k%2))
			{
				double d = 0.025L;
				if(lat < 0.0L)
				{
					if(!k)
						d = 0;
					sprintf(tmp, "%d", 12 + k / 2);
				}else
					sprintf(tmp, "%d", 12 - k / 2);
				right_ascension = tmp;
				text->loadText(renderer, right_ascension, redColor);
				SDL_Point p = { 0, - 727 / 2 };
				SDL_Rect clip = {0, 0, 768, 768};
				text->render(renderer, 768 / 2, 750, NULL, -(i + theta) * 180.0L / M_PI, &p);
				if(lat < 0.0L)
				{
					sprintf(tmp, "%d", k / 2);
				}else{
					if(!k){
						sprintf(tmp, "%d", 0);
						d = 0;
					}else
						sprintf(tmp, "%d", 24 - k / 2);
				}
				right_ascension = tmp;
				text->loadText(renderer, right_ascension, redColor);
				text->render(renderer, 768 / 2, 755, NULL, -(i + theta - d) * 180.0L / M_PI + 180.0L, &p);
				c4.radius_change(c, -15.0L);
				c5.radius_change(c, -15.0L);
			}else{
				c4.radius_change(c, -50.0L);
				c5.radius_change(c, -50.0L);
			}
			k++;
		}else if(!(j % 2)){
			c4.radius_change(c, -40.0L);
			c5.radius_change(c, -40.0L);
		}else{
			c4.radius_change(c, -20.0L);
			c5.radius_change(c, -20.0L);
		}
		lineRGBA(renderer, (int)(c4.getPosX()), (int)(c4.getPosY()), (int)(c5.getPosX()), (int)(c5.getPosY()), 0xFF, 0x00, 0x00, 0xFF);
		j++;
	}
	
	return EXIT_SUCCESS;
}


int draw_controls(SDL_Renderer *renderer, Media *text, SDL_Color redColor, std::list<Button*> buttons, int hours, int minutes, int days, int months, int years, int latitudes)
{
	char hour[20], day[20], month[20], year[20], latitude[20];
	for(auto it = buttons.begin(); it != buttons.end(); ++it)
		(*it)->render(renderer);
	sprintf(hour, "%d h       %d '", hours, minutes);
	std::string hours_disp = hour;
	sprintf(day, "%d days", days);
	std::string days_disp = day;
	sprintf(month, "%d months", months);
	std::string months_disp = month;
	sprintf(year, "%d years", years);
	std::string years_disp = year;
	sprintf(year, "%d latitude", latitudes);
	std::string latitudes_disp = year;
	text->loadText(renderer, hours_disp, redColor);
	text->render(renderer, 50, 100);
	text->loadText(renderer, days_disp, redColor);
	text->render(renderer, 50, 200);
	text->loadText(renderer, months_disp, redColor);
	text->render(renderer, 50, 300);
	text->loadText(renderer, years_disp, redColor);
	text->render(renderer, 50, 400);
	text->loadText(renderer, latitudes_disp, redColor);
	text->render(renderer, 50, 500);
	text->loadText(renderer, "J2000", redColor);
	text->render(renderer, 100, 25);

	return EXIT_SUCCESS;
}

int display_stars_features(SDL_Renderer *renderer, StarsUtils *utils, Media *text, int x , int y , SDL_Color redColor, double lat)
{
	Star *s = NULL;
	std::list<Star*> stars = utils->getStars();
	for(auto it = stars.begin(); it != stars.end(); ++it)
	{
		if((*it)->over(x, y))
		{
			s = *it;
			break;
		}
	}
	if(s != NULL)
	{
		char tmp[200];
		
		text->loadText(renderer, s->getConstellation(), redColor);
		text->render(renderer, 0, 580);
		text->loadText(renderer, s->getName(), redColor);
		text->render(renderer, 0, 610);
		double hours = s->getRightAscension() * 12.0L / M_PI;
		if(lat < 0.0L)
			hours = 24.0L - hours;
		double minutes = (hours - floor(hours)) * 60.0L;
		double seconds = (minutes - floor(minutes)) * 60.0L;
		sprintf(tmp, "right ascension: %d h %d ' %d ''", static_cast<int>(hours), static_cast<int>(minutes), static_cast<int>(seconds));
		std::string ra = tmp;
		tmp[0] = '\0';
		text->loadText(renderer, ra, redColor);
		text->render(renderer, 0, 640);
		hours = s->getDeclination() * 180.0L / M_PI;
		if(lat < 0.0L)
			hours = -hours;

		double h = (hours<0)?-hours: hours;
		minutes = (h - floor(h)) * 60.0L;
		seconds = (minutes - floor(minutes)) * 60.0L;
		sprintf(tmp, "declination: %d \xB0 %d ' %d ''", static_cast<int>(hours), static_cast<int>(minutes), static_cast<int>(seconds));
		std::string dec = tmp;
		tmp[0] = '\0';
		text->loadText(renderer, dec, redColor);
		text->render(renderer, 0, 670);
		sprintf(tmp, "magnitude: %.1f", static_cast<float>(s->getMagnitude()));
		std::string mag = tmp;
		tmp[0] = '\0';
		text->loadText(renderer, mag, redColor);
		text->render(renderer, 0, 700);
		sprintf(tmp, "Light Years: %d", s->getLightYears());
		std::string al = tmp;
		tmp[0] = '\0';
		text->loadText(renderer, al, redColor);
		text->render(renderer, 0, 730);
	}

	return EXIT_SUCCESS;
}



