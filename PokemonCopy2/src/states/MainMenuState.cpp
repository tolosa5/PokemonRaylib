#include "MainMenuState.hpp"

MainMenuState::MainMenuState(std::stack<State*>* states) : 
    State(states)
{
    background.x = 0;
    background.y = 0;
    background.width = GetScreenWidth();
    background.height = GetScreenHeight();

    font = LoadFont("assets/fonts/monogram.ttf");

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
            PlayButtonClick(); });

    buttons["EXIT_BUTTON"] = new Button({100, 200, 200, 50}, "Exit", &font);
    buttons["EXIT_BUTTON"]->onClick.Subscribe(
        [&]() {
            ExitButtonClick(); });
}

void MainMenuState::Update(float deltaTime)
{
    UpdateInputs(deltaTime);
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

void MainMenuState::PlayButtonClick()
{
    states->push(new GameState(states));
}

void MainMenuState::ExitButtonClick()
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
    quit = true;
}