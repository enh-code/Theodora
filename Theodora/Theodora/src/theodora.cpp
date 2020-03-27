#include "theodora.h"

Theodora game;

int Theodora::tstart()
{
	int code = SDL_Init(SDL_INIT_EVERYTHING);
	if (code != 0)
	{
		return 1;
	}

	window = SDL_CreateWindow("Theodora Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		return 2;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		return 3;
	}

	return 0;
}

void Theodora::texit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Theodora::wpos(int x, int y)
{
	SDL_SetWindowPosition(window, x, y);
}

void Theodora::wsize(int w, int h)
{
	SDL_SetWindowSize(window, w, h);
}




int main(int argc, char** argv)
{
	int code = game.tstart();
	if (code != 0)
	{
		goto end;
	}

	code = game.init();
	if (code != 0)
	{
		goto end;
	}

	game.loop();

	end:
	game.texit();
	return code;
}