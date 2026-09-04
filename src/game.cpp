#include "game.hpp"
#include "raymath.h"
#include <cmath>

Game::Game() {
    InitWindow(1280, 720, "The Nine Worlds");
    SetTargetFPS(60);

    camera.position = { 10, 10, 10 };
    camera.target = { 0, 0, 0 };
    camera.up = { 0, 1, 0 };
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    Vector2 mouseDelta = GetMouseDelta();

    yaw -= mouseDelta.x * 0.01f;
    pitch -= mouseDelta.y * 0.01f;

    pitch = Clamp(pitch, -PI / 2.0f + 0.01f, PI / 2.0f - 0.01f);

    Vector3 direction = {
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    };

    float speed = 0.1f;

    if (IsKeyDown(KEY_W)) {
        camera.position = Vector3Add(
            camera.position,
            Vector3Scale(direction, speed)
        );
    }

    if (IsKeyDown(KEY_S)) {
        camera.position = Vector3Subtract(
            camera.position,
            Vector3Scale(direction, speed)
        );
    }
    if (IsKeyDown(KEY_A)) {
        Vector3 right = Vector3CrossProduct(direction, camera.up);
        camera.position = Vector3Subtract(
            camera.position,
            Vector3Scale(right, speed)
        );
    }   
    if (IsKeyDown(KEY_D)) {
        Vector3 right = Vector3CrossProduct(direction, camera.up);
        camera.position = Vector3Add(
            camera.position,
            Vector3Scale(right, speed)
        );
    }

    camera.target = Vector3Add(camera.position, direction);
}

void Game::draw() {
    BeginDrawing();

    ClearBackground(SKYBLUE);

    BeginMode3D(camera);

    DrawCube(
        { 0, 1, 0 },  // position
        2,             // width
        2,             // height
        2,             // length
        RED            // color
    );

    DrawGrid(20, 1.0f);

    EndMode3D();

    EndDrawing();
}