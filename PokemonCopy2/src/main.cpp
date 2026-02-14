#include <raylib.h>
#include "src/core/Game.hpp"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    // Initialize game
    Game game;
    game.Initialize(screenWidth, screenHeight, "Pokemon Copy Game");

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        game.Update();
        
        // Draw
        BeginDrawing();
        ClearBackground(GRAY);
        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}