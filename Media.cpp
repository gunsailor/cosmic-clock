#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include"Media.h"


Media::Media()
{
	//Initialize
	font = NULL;
	texture = NULL;
	position = {0, 0, 0, 0};
}

Media::~Media()
{
	//Deallocate
	free();
}

bool Media::loadTTF(std::string p, int size)
{
	bool success = true;
	font = TTF_OpenFont( p.c_str(), size );
	if( font == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	return success;
}

bool Media::loadImage(SDL_Renderer* renderer, std::string path)
{
	free();
	
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        	newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			position.w = loadedSurface->w;
			position.h = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	texture = newTexture;
	return texture != NULL;
}

bool Media::loadText(SDL_Renderer* renderer, std::string textureText, SDL_Color textColor )
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( this->font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
        	texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			position.w = textSurface->w;
			position.h = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}
	
	return texture != NULL;
}

void Media::free()
{
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
	}
}

void Media::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( texture, red, green, blue );
}

void Media::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( texture, blending );
}
		
void Media::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( texture, alpha );
}

void Media::setRect(int x, int y, int w, int h)
{
	position.x = x;
	position.y =y;
	position.w = w;
	position.h =h;
}
void Media::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, position.w, position.h};
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

int Media::getWidth()
{
	return position.w;
}

int Media::getHeight()
{
	return position.h;
}

