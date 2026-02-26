#include "EditorState.hpp"

EditorState::EditorState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    font = LoadFont("assets/fonts/monogram.ttf");

    InitBackground();
    InitButtons();
    InitTileMap();
}

EditorState::~EditorState()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    //delete buttonGroup;
    delete tileMap;
}

void EditorState::InitBackground()
{
    
}

void EditorState::InitGui()
{
    selectorRect = { 0, 0, gridSize, gridSize };
}

void EditorState::InitButtons()
{
    
    
    for (const auto& button : buttons)
    {
        buttonVector.push_back(button.second);
    }

    //buttonGroup = new ButtonGroup(buttonVector, VERTICAL);
}

void EditorState::InitTileMap()
{
    tileMap = new TileMap(gridSize, 10, 10);
}

void EditorState::Update(float deltaTime)
{
    State::Update(deltaTime);
    UpdateEditorInputs();
    UpdateInputs(deltaTime);
    UpdateGui();
    UpdateButtons();
}

void EditorState::Draw()
{
    DrawRectangleLinesEx(selectorRect, 2, GREEN);
    DrawButtons();
    tileMap->Draw();
}

void EditorState::DrawButtons()
{
    for (const auto& button : buttons)
    {
        button.second->Draw();
    }
}

void EditorState::UpdateButtons()
{
    //buttonGroup->Update();
}

void EditorState::UpdateGui()
{
    selectorRect.x = mousePosGrid.x * gridSize;
    selectorRect.y = mousePosGrid.y * gridSize;
}

void EditorState::UpdateEditorInputs()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        tileMap->AddTile(mousePosGrid.x, mousePosGrid.y, 0);
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        tileMap->RemoveTile(mousePosGrid.x, mousePosGrid.y, 0);
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

