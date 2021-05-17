#ifndef __MEDIA_H
#define __MEDIA_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>
#include<iostream>

class Media
{
	public:
		Media();

		~Media();

		bool loadImage(SDL_Renderer* renderer, std::string path);
		
		bool loadTTF(std::string path, int size);
		
		bool loadText( SDL_Renderer * renderer, std::string textureText, SDL_Color textColor );

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );
		
		void setRect(int x, int y, int w, int h);
		
		SDL_Rect getRect()
		{
			return position;
		}
		void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();

	protected:
		SDL_Texture* texture;
		SDL_Rect position;
		TTF_Font *font;
	private:
		void free();
};

#endif
