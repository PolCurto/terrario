#include "Inputs.h"

#include <SDL3/SDL.h>
#include <iostream>

bool Inputs::Create()
{
	if (!SDL_Init(SDL_INIT_EVENTS)) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Inputs::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			return false;
		}
	}

	keyboard = SDL_GetKeyboardState(NULL);
	return true;
}

bool Inputs::Destroy()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}