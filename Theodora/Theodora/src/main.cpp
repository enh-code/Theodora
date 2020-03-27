#include "theodora.h"

TObject space, star, player;

int Theodora::init()
{
	int code = 0;
	wpos(0, 30);
	wsize(1920, 1010);

	space = TObject(renderer, 920, 465, 80, 80);
	star = TObject(renderer, 920, 465, 80, 80, 10000);
	player = TObject(renderer, 640, 465, 20, 30);

	code = space.loadTexture("assets/space.png");
	if(code != 0)
	{
		return code;
	}

	code = star.loadTexture("assets/star.png", 0xFF, 0xFF, 0xFF);
	if (code != 0)
	{
		return code;
	}

	code = player.loadTexture("assets/player.png", 0xFF, 0xFF, 0xFF);
	if (code != 0)
	{
		return code;
	}

	return 0;
}

int Theodora::loop()
{
	tmath::Vector gravity;
	SDL_Event e;

	while(true)
	{
		if(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					goto end;
					break;
				case SDL_KEYDOWN:
					if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						goto end;
					}
					break;
			}
		}

		const Uint8* keyboard = SDL_GetKeyboardState(NULL);
		player.velocity = tmath::Vector(keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A], keyboard[SDL_SCANCODE_S] - keyboard[SDL_SCANCODE_W]);
		player.velocity.setLength(-10);
		player.setPos(player.getRect()->x + player.velocity.getX(), player.getRect()->y + player.velocity.getY());

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		space.render(NULL, NULL);
		star.render(NULL, star.getRect());
		player.render(NULL, player.getRect());
		SDL_RenderPresent(renderer);
	}

	end:
	return 0;
}