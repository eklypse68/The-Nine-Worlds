#pragma once

#include "raylib.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void update();
    void draw();

    Camera3D camera;

    float yaw = 0.0f;
    float pitch = 0.0f;
};