#pragma once
#ifndef THEODORA_H
#define THEODORA_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include "tobject.h"
#include "tmath.h"

class Theodora
{
	public:
		int tstart();
		int init();
		int loop();
		void texit();

		void wpos(int x, int y);
		void wsize(int w, int h);

	protected:
		SDL_Window* window;
		SDL_Renderer* renderer;
};

int main(int arc, char** argv);

#endif