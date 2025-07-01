#include "Inputs.h"

#include <SDL3/SDL_events.h>

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