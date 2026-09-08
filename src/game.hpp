#pragma once

#include "r3d/r3d_lighting.h"


class Game
{
public:
    bool init();
    void run();
    void shutdown();
    void update();
    void render();

private:
    bool running = false;
    R3D_Light light;
    R3D_Light light2;
 
};