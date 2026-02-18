#include "MainMenuState.hpp"

MainMenuState::MainMenuState()
{
    background.x = 0;
    background.y = 0;
    background.width = GetScreenWidth();
    background.height = GetScreenHeight();

    InitButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::InitButtons()
{
    buttons["GAME_STATE_BUTTON"] = new Button({100, 100, 200, 50}, "Play", &font);
    buttons["GAME_STATE_BUTTON"]->onClick.Subscribe(
        [&]() {
            OnPlayButtonClick(); });
}

void MainMenuState::Update(float deltaTime)
{
    for (auto& button : buttons)
    {
        button.second->Update(GetMousePosition());
    }
}

void MainMenuState::Draw()
{
    DrawRectangleRec(background, DARKGRAY);
    DrawButtons();
}

void MainMenuState::DrawButtons()
{
    for (const auto& button : buttons)
    {
        button.second->Draw();
    }
}

void MainMenuState::OnPlayButtonClick()
{
    quit = true;
}

void MainMenuState::UpdateInputs(float deltaTime)
{
    CheckForQuit();
    for (const auto& button : buttons)
    {
        button.second->Update(GetMousePosition());
    }
}

void MainMenuState::EndState()
{

}

void MainMenuState::CheckForQuit()
{
    if (IsKeyPressed(KEY_ESCAPE))
        quit = true;
}