#include "src/core/Game.hpp"
#include "src/managers/CanvasManager.hpp"
#include "src/managers/AudioManager.hpp"

#include <iostream>
#include <fstream>

Game::Game()
{

}

Game::~Game()
{
    while (!states.empty())
    {
        states.top()->EndState();
        delete states.top();
        states.pop();
    }
}

void Game::Initialize(int width, int height, const char* title)
{
    screenWidth = width;
    screenHeight = height;
    InitWindow(screenWidth, screenHeight, title);

    SetTargetFPS(60);
    InitAudioDevice();
    InitStates();
}

void Game::InitStates()
{
    states.push(new MainMenuState());
    states.push(new GameState());
}

void Game::Draw()
{
    if (!states.empty())
        states.top()->Draw();

}

void Game::Update(float deltaTime)
{
    if (!states.empty())
    {
        states.top()->Update(deltaTime);
        if (states.top()->GetQuit())
        {
            states.top()->EndState();
            delete states.top();
            states.pop();
        }
    }
}

void Game::HandleInput()
{
    
}