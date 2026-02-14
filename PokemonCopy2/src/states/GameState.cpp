#include "src/states/GameState.hpp"

GameState::GameState(std::map<std::string, int>* supportedKeys) : 
player({100, 100}), State(supportedKeys)
{
    InitKeybinds();
}

GameState::~GameState()
{

}

void GameState::Update()
{
    UpdateInputs();
    player.Update();
}

void GameState::Draw()
{
    player.Draw();
}

void GameState::InitKeybinds()
{
    keybinds.emplace("MOVE_LEFT", supportedKeys->at("A"));
    keybinds.emplace("MOVE_RIGHT", supportedKeys->at("D"));
    keybinds.emplace("MOVE_UP", supportedKeys->at("W"));
    keybinds.emplace("MOVE_DOWN", supportedKeys->at("S"));
}

void GameState::UpdateInputs()
{
    CheckForQuit();

    if (IsKeyDown(KEY_LEFT))
        player.Move({-1, 0});

    else if (IsKeyDown(KEY_RIGHT))
        player.Move({1, 0});

    else if (IsKeyDown(KEY_UP))
        player.Move({0, -1});

    else if (IsKeyDown(KEY_DOWN))
        player.Move({0, 1});
}

void GameState::EndState()
{

}

void GameState::CheckForQuit()
{

}
