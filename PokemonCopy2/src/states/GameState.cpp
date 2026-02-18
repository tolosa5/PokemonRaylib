#include "src/states/GameState.hpp"

GameState::GameState() : player({100, 100}, PLAYER)
{
    
}

GameState::~GameState()
{

}

void GameState::Update(float deltaTime)
{
    UpdateInputs(deltaTime);
    player.Update(deltaTime);
}

void GameState::Draw()
{
    player.Draw();
}

void GameState::UpdateInputs(float deltaTime)
{
    CheckForQuit();
    if (IsKeyDown(KEY_A))
        player.Move({-1, 0});

    else if (IsKeyDown(KEY_D))
        player.Move({1, 0});

    else if (IsKeyDown(KEY_W))
        player.Move({0, -1});

    else if (IsKeyDown(KEY_S))
        player.Move({0, 1});
}

void GameState::EndState()
{

}

void GameState::CheckForQuit()
{
    if (IsKeyPressed(KEY_ESCAPE))
        quit = true;
}
