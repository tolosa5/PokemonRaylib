#include "MainMenuState.hpp"
#include "src/ui/ButtonGroup.hpp"

MainMenuState::MainMenuState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    font = LoadFont("assets/fonts/monogram.ttf");

    InitBackground();
    InitButtons();
    InputManager::SetCurrentMode(UI);
}

MainMenuState::~MainMenuState()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    delete buttonGroup;
}

void MainMenuState::InitBackground()
{
    backgroundTexture = LoadTexture("assets/graphics/main_menu.png");
    backgroundTexture.width = GetScreenWidth();
    backgroundTexture.height = GetScreenHeight();
}

void MainMenuState::InitButtons()
{
    buttons["GAME_STATE_BUTTON"] = new Button({100, 100, 200, 50}, "Play", &font);
    buttons["GAME_STATE_BUTTON"]->onClick.Subscribe(
        [&]() {
            PlayButtonClick(); });
    buttonVector.push_back(buttons["GAME_STATE_BUTTON"]);

    buttons["SETTINGS_BUTTON"] = new Button({100, 150, 200, 50}, "Settings", &font);
    buttonVector.push_back(buttons["SETTINGS_BUTTON"]);
    
    buttons["EDITOR_BUTTON"] = new Button({100, 200, 200, 50}, "Editor", &font);
    buttons["EDITOR_BUTTON"]->onClick.Subscribe(
        [&]() {
            EditorButtonClick(); });
    buttonVector.push_back(buttons["EDITOR_BUTTON"]);

    buttons["EXIT_BUTTON"] = new Button({100, 250, 200, 50}, "Exit", &font);
    buttons["EXIT_BUTTON"]->onClick.Subscribe(
        [&]() {
            ExitButtonClick(); });
    buttonVector.push_back(buttons["EXIT_BUTTON"]);
            
    buttonGroup = new ButtonGroup(buttonVector, VERTICAL, 0, 0);
}

void MainMenuState::Update(float deltaTime)
{
    UpdateInputs(deltaTime);
    buttonGroup->Update();
}

void MainMenuState::Draw()
{
    DrawTexture(backgroundTexture, 0, 0, WHITE);
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
    states->push(new GameState(states, gridSize));
}

void MainMenuState::ExitButtonClick()
{
    quit = true;
}

void MainMenuState::EditorButtonClick()
{
    states->push(new EditorState(states, gridSize));
}

void MainMenuState::UpdateInputs(float deltaTime)
{
    for (const auto& button : buttons)
    {
        button.second->Update();
    }

    if (IsKeyPressed(KEY_ESCAPE))
        EndState();
}