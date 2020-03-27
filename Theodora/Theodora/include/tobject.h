#pragma once
#ifndef TOBJECT_H
#define TOBJECT_H

#include <SDL.h>
#include "tmath.h"

class TObject
{
	public:
		TObject();
		TObject(SDL_Renderer* r, int x, int y, int w, int h, float mass = 1);
		~TObject();

		int loadTexture(const char* path);
		int loadTexture(const char* path, Uint8 r, Uint8 g, Uint8 b);
		//float distanceTo(TObject* obj);
		//float angleTo(TObject* obj); BROKEN??
		virtual void render(SDL_Rect* srcrect, SDL_Rect* dstrect);

		void setPos(int x, int y);
		SDL_Rect* getRect();
		float getMass();

		tmath::Vector velocity;

	protected:
		float mass;
		SDL_Rect rect;
		SDL_Renderer* r;
		SDL_Texture* texture;
};

#endif