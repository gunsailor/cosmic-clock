#ifndef __BUTTON_H
#define __BUTTON_H

#include"Media.h"
#include<SDL2/SDL.h>

class Button{
	public:
		Button(SDL_Renderer *renderer, std::string path, int min ,int max);
		Button(SDL_Renderer *renderer, std::string path, std::string path1);
		~Button();
		int setRect(int x, int y, int w, int h);
		int action(int *scope, int step, int x,int y, int *update = NULL);
		int action(SDL_Renderer *renderer, double *scope, int x,int y, int *update = NULL);
		int render(SDL_Renderer *renderer);
	private:
		Media media;
		int min;
		int max;
		std::string path, path1;
};
#endif
