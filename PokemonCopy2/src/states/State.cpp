#include "src/states/State.hpp"
#include "State.hpp"

State::State()
{
    quit = false;
}

State::~State()
{

}

void State::CheckForQuit()
{
    if (IsKeyPressed(KEY_ESCAPE))
        quit = true;
}

void State::UpdateMousePositions()
{
    mousePosScreen = GetMousePosition();
    mousePosWindow = GetScreenToWorld2D(mousePosScreen, (Camera2D){0});
    
}