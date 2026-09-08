#include <math.h>


#include "game.hpp"
#include "controls.hpp" 
#include "worlds/midgardr/midgardr.hpp"  
#include "renderer/Lighting.hpp"

namespace {
    Controls controls;
}

namespace {
    Midgard midgard;
}

bool Game::init()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920, 1080, "The Nine Worlds");
    R3D_Init(1920, 1080);

    Image icon = LoadImage("assets/icon2.png");

    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetWindowMinSize(1280, 720);
    SetWindowMaxSize(5120, 2880);

    DisableCursor();
    controls.init();
    midgard.init();


    Color lightColor = WHITE;

    light = R3D_CreateOmniLight(
        { -0.0f, 5.0f, 5.0f },
        15.0f,
        lightColor,
        5.0f
    );

    light2 = R3D_CreateOmniLight(
        { 20.0f, 5.0f, 5.0f },
        15.0f,
        lightColor,
        5.0f
    );

    return true;
}   

void Game::update() {
    
}

void Game::render() {
        BeginDrawing();
        ClearBackground(BLUE);
        R3D_Begin(controls.camera);
        controls.update(); 

        addOmniLight(
            { -0.0f, 5.0f, 5.0f },
            15.0f,
            WHITE,
            5.0f
        );
        addOmniLight(
            { 20.0f, 5.0f, 5.0f },
            15.0f,
            WHITE,
            5.0f
        );  
        addOmniLight(
            { 40.0f, 5.0f, 5.0f },
            15.0f,
            WHITE,
            5.0f
        );  

        DrawPlane(
        { 0.0f, -10.0f, 0.0f },
        { 50.0f, 50.0f },
        GREEN   
        );

        midgard.render();
        
        R3D_End();

        EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        update();
        midgard.update();
        render();
    }
}

void Game::shutdown()
{
    midgard.shutdown();
    R3D_Close();
    CloseWindow();
}   