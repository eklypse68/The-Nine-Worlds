#pragma once

#include "raylib.h"

class Controls {
    private:
        Vector3 position;
        Vector3 target;
        Vector3 up;
        float fovy;
        float aspect;
        float nearPlane;
        float farPlane;

        float yaw = 0.0f;
        float pitch = 0.0f;

        float verticalVelocity = 0.0f;
        float gravity = 9.81f;
        float jumpStrength = 7.0f;

        
    public:
        Camera3D camera{};

        void update();
        void init();

    
};