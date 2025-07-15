#include "Inputs.h"

#include "Window.h"

#include <SDL3/SDL.h>
#include <iostream>

constexpr int MOUSE_BUTTONS = 5;

bool Inputs::Create()
{
	if (!SDL_Init(SDL_INIT_EVENTS)) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	keyboard = new KeyState[SDL_SCANCODE_COUNT];
	mouse_buttons = new KeyState[MOUSE_BUTTONS];

	return true;
}	

bool Inputs::Update(Window& window)
{

	// Update mouse button states
	for (int i = 0; i < MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KeyState::Down) mouse_buttons[i] = KeyState::Hold;
		else if (mouse_buttons[i] == KeyState::Up) mouse_buttons[i] = KeyState::Idle;
	}

	// Poll events
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			return false;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			mouse_pos.x = event.motion.x;
			mouse_pos.y = event.motion.y;
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			mouse_buttons[event.button.button - 1] = KeyState::Down;
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			mouse_buttons[event.button.button - 1] = KeyState::Up;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			window.UpdateWindowSize();
			break;
		}

	}

	// Update key states
	const bool* keys = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
	{
		if (keys[i])
		{
			if (keyboard[i] == KeyState::Idle || keyboard[i] == KeyState::Up) keyboard[i] = KeyState::Down;
			else keyboard[i] = KeyState::Hold;
		}
		else
		{
			if (keyboard[i] == KeyState::Hold || keyboard[i] == KeyState::Down) keyboard[i] = KeyState::Up;
			else keyboard[i] = KeyState::Idle;
		}
	}


	return true;
}

bool Inputs::Destroy()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}