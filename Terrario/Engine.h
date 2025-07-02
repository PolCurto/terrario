#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Inputs.h"
#include "Timer.h"

struct Engine
{
    Window window{};
    Renderer renderer{};
    Inputs inputs{};
    Timer timer{};
};