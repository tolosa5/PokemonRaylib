#include "EditorState.hpp"

EditorState::EditorState(std::stack<State*>* states) : 
    State(states)
{
    font = LoadFont("assets/fonts/monogram.ttf");

    InitBackground();
    InitButtons();


}

EditorState::~EditorState()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    //delete buttonGroup;
}

void EditorState::InitBackground()
{
    backgroundTexture = LoadTexture("assets/graphics/main_menu.png");
    backgroundTexture.width = GetScreenWidth();
    backgroundTexture.height = GetScreenHeight();
}

void EditorState::InitButtons()
{
    buttons["GAME_STATE_BUTTON"] = new Button({100, 100, 200, 50}, "Play", &font);
    buttons["GAME_STATE_BUTTON"]->onClick.Subscribe(
        [&]() {
            PlayButtonClick(); });

    buttons["GAME_STATE_BUTTON"]->SetButtonState(HOVER);

    buttons["SETTINGS_BUTTON"] = new Button({100, 150, 200, 50}, "Settings", &font);

    buttons["EXIT_BUTTON"] = new Button({100, 200, 200, 50}, "Exit", &font);
    buttons["EXIT_BUTTON"]->onClick.Subscribe(
        [&]() {
            ExitButtonClick(); });
            
    for (const auto& button : buttons)
    {
        buttonVector.push_back(button.second);
    }

    //buttonGroup = new ButtonGroup(buttonVector, VERTICAL);
}

void EditorState::Update(float deltaTime)
{
    UpdateInputs(deltaTime);
}

void EditorState::Draw()
{
    DrawTexture(backgroundTexture, 0, 0, WHITE);
    DrawButtons();
}

void EditorState::DrawButtons()
{
    for (const auto& button : buttons)
    {
        button.second->Draw();
    }
}

void EditorState::PlayButtonClick()
{
    //states->push(new GameState(states));
}

void EditorState::ExitButtonClick()
{
    quit = true;
}

void EditorState::UpdateInputs(float deltaTime)
{
    for (const auto& button : buttons)
    {
        button.second->Update();
    }

    if (IsKeyPressed(KEY_ESCAPE))
        EndState();
}

