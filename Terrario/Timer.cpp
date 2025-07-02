#include "Timer.h"

#include <SDL3/SDL_timer.h>

void Timer::Tick()
{
    delta_time = (float)(SDL_GetTicksNS() - lastTick) / 1000000.0f;
    elapsed_time += delta_time;
    lastTick = SDL_GetTicksNS();
}