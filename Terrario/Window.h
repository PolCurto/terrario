#pragma once

#include <stdint.h>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_FRect;

struct Window
{
	bool Create();
	void Destroy();

	void Render();
	void RenderRect(const SDL_FRect& rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void RenderDebugText(const std::string& text, float x, float y);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};