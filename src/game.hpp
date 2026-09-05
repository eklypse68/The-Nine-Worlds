#pragma once

class Game
{
public:
    bool init();
    void run();
    void shutdown();

private:
    bool running = false;
};