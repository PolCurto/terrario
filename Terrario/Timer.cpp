#include "Timer.h"

#include "Inputs.h"

#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_scancode.h>

void Timer::Tick(const Inputs& inputs)
{
    float time_scale = 1.0f;
    if (inputs.keyboard[SDL_SCANCODE_F3] == KeyState::Hold) time_scale = 50.0f;

    delta_time = (float)(SDL_GetTicksNS() - lastTick) / 1000000.0f * time_scale;
    elapsed_time += delta_time;
    lastTick = SDL_GetTicksNS();
}