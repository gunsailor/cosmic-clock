#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"Button.h"

Button::Button(SDL_Renderer *renderer, std::string path, int min, int max)
{
	this->min = min;
	this->max = max;
	this->path = path;
	media.loadImage(renderer, path);
	//SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, 255, 255, 255));
}

Button::Button(SDL_Renderer *renderer, std::string path, std::string path1)
{
	this->path = path;
	this->path1 = path1;
	media.loadImage(renderer, path);
	//SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format, 255, 255, 255));
}

int Button::setRect(int x, int y, int w, int h)
{
	media.setRect(x, y, w, h);
	return EXIT_SUCCESS;
}

int Button::action(int *scope, int step, int x, int y, int *update)
{
	if(x > media.getRect().x && x < (media.getRect().x + media.getRect().w) && y > media.getRect().y && y < (media.getRect().y + media.getRect().h))
	{
		if(((*scope) + step) > this->max)
			(*scope) = this->min;
		else if(((*scope) + step) < this->min)
			(*scope) = this->max;
		else
			(*scope) += step;
		if(update != NULL)
			*update = 1;
	}

	return EXIT_SUCCESS;
}

int Button::action(SDL_Renderer *renderer, double *scope, int x, int y, int *update)
{
	if(x > media.getRect().x && x < (media.getRect().x + media.getRect().w) && y > media.getRect().y && y < (media.getRect().y + media.getRect().h))
	{
		*scope = -*scope;
		if(*scope > 0.0L)
			media.loadImage(renderer, path);
		else
			media.loadImage(renderer, path1);
		*update = 1;
	}

	return EXIT_SUCCESS;
}

int Button::render(SDL_Renderer *renderer)
{
	media.render(renderer, media.getRect().x, media.getRect().y);
	return EXIT_SUCCESS;
}

Button::~Button()
{

}
