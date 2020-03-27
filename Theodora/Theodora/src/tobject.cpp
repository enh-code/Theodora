#include "TObject.h"
#include <SDL_image.h>

TObject::TObject()
{
	this->r = NULL;
	this->rect = {0, 0, 0, 0};
	this->texture = NULL;
	this->mass = 0;
}

TObject::TObject(SDL_Renderer* r, int x, int y, int w, int h, float mass)
{
	this->r = r;
	this->rect = {x, y, w, h};
	this->texture = NULL;
	this->mass = mass;
}

TObject::~TObject()
{
	SDL_DestroyTexture(texture);
}

int TObject::loadTexture(const char *path)
{
	SDL_Surface* load = IMG_Load(path);
	if(load == NULL)
	{
		return 1;
	}

	texture = SDL_CreateTextureFromSurface(r, load);
	if(texture == NULL)
	{
		return 2;
	}

	return 0;
}

int TObject::loadTexture(const char* path, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* load = IMG_Load(path);
	if(load == NULL)
	{
		return 1;
	}
	
	int code = SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, r, g, b));
	if(code != 0)
	{
		return code;
	}

	texture = SDL_CreateTextureFromSurface(this->r, load);
	if(texture == NULL)
	{
		return 2;
	}

	return 0;
}
/*
float TObject::distanceTo(TObject* obj)
{
	int x = obj->getRect()->x + (obj->getRect()->w / 2) - rect.x;
	int y = obj->getRect()->y + (obj->getRect()->h / 2) - rect.y;
	return sqrtf(x * x + y * y);
}

float TObject::angleTo(TObject* obj)
{
	return atan2f(obj->getRect()->y + (obj->getRect()->h / 2) - rect.y, obj->getRect()->x + (obj->getRect()->w / 2) - rect.x);
}*/

void TObject::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

SDL_Rect* TObject::getRect()
{
	return &rect;
}

void TObject::render(SDL_Rect* srcrect, SDL_Rect* dstrect)
{
	SDL_RenderCopy(r, texture, srcrect, dstrect);
}

float TObject::getMass()
{
	return mass;
}