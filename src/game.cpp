#include "game.hpp"

#include <SDL3/SDL.h>
#include <chrono>
#include <thread>

bool Game::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        return false;

    window = SDL_CreateWindow(
        "The Nine Worlds",
        1280,
        720,
        0
    );

    if (!window)
    {
        SDL_Quit();
        return false;
    }

    running = true;

    return true;
}

void Game::run()
{
    using Clock = std::chrono::steady_clock;

    constexpr double targetFrameTime = 1.0 / 60.0;

    while (running)
    {
        auto frameStart = Clock::now();

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // Game update goes here.

        // Rendering goes here.

        auto frameEnd = Clock::now();

        std::chrono::duration<double> elapsed = frameEnd - frameStart;

        double remaining = targetFrameTime - elapsed.count();

        if (remaining > 0.0)
        {
            std::this_thread::sleep_for(
                std::chrono::duration<double>(remaining)
            );
        }
    }
}

void Game::shutdown()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}