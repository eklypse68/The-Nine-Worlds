#pragma once

#include <SDL3/SDL.h>

class Game
{
public:
bool init();
void run();
void shutdown();

private:
SDL_Window* window = nullptr;
bool running = false;
};
