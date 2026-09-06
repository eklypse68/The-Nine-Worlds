#include "game.hpp"

#include <SDL3/SDL.h>
#include <chrono>

#include <bgfx/bgfx.h>

bool Game::init()
{
    // 1. Start SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
        return false;

    // 2. Create SDL window
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

    // 3. Get the native Windows window handle
    auto props = SDL_GetWindowProperties(window);

    void* hwnd = SDL_GetPointerProperty(
        props,
        SDL_PROP_WINDOW_WIN32_HWND_POINTER,
        nullptr
    );

    // 4. Give that handle to bgfx
    bgfx::Init init{};

    init.swapChain.nwh = hwnd;
    init.swapChain.width = 1280;
    init.swapChain.height = 720;

    if (!bgfx::init(init))
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    bgfx::setViewClear(
    0,
    BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
    0xff0000ff,
    1.0f,
    0
    );

    bgfx::setViewRect(
        0,
        0,
        0,
        1280,
        720
    );

    running = true;
    return true;
}

void Game::run()
{
    using Clock = std::chrono::steady_clock;

    auto previousFrame = Clock::now();

    while (running)
    {
        auto currentFrame = Clock::now();

        std::chrono::duration<double> elapsed =
            currentFrame - previousFrame;

        double deltaTime = elapsed.count();

        previousFrame = currentFrame;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }
        bgfx::touch(0);
        bgfx::frame();
    }
}

void Game::shutdown()
{
    bgfx::shutdown();

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}