#include "EditorState.hpp"

EditorState::EditorState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    font = LoadFont("assets/fonts/monogram.ttf");

    InitBackground();
    InitButtons();
    InitTexts();
    InitTileMap();
    InitTextureSelector();
    InitGui();

    selectedSheetTile = { 0, 0 };
    paintedRect = { 0, 0, gridSize, gridSize };
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
    delete textureSelector;
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

void EditorState::InitTextureSelector()
{
    textureSelector = new TextureSelector(
        { 32, 32 }, { 256, 600 }, gridSize, tileMap->GetTextureSheet());
}

void EditorState::InitTexts()
{
    cursorText = "Editor Mode";
}

void EditorState::InitTileMap()
{
    tileMap = new TileMap(gridSize, 20, 20);
}

void EditorState::Update(float deltaTime)
{
    UpdateMousePositions();
    UpdateEditorInputs();
    UpdateInputs(deltaTime);
    UpdateGui();
    UpdateButtons();
    tileMap->Update();
}

void EditorState::Draw()
{
    tileMap->Draw();
    textureSelector->Draw();
    DrawButtons();

    if (!textureSelector->IsActive())
        DrawRectangleLinesEx(selectorRect, 2, GREEN);
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
    textureSelector->Update(GetMousePosition());
    if (!textureSelector->IsActive())
    {
        selectorRect.x = mousePosGrid.x * gridSize;
        selectorRect.y = mousePosGrid.y * gridSize;
    }
}

void EditorState::UpdateEditorInputs()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (!textureSelector->IsActive())
            tileMap->AddTile(mousePosGrid.x, mousePosGrid.y, 0, paintedRect);
        else
        {
            paintedRect = textureSelector->GetSelectedRect();
            std::cout << "Selected Rect: " << paintedRect.x << ", " << paintedRect.y 
                << ", " << paintedRect.width << ", " << paintedRect.height << std::endl;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (!textureSelector->IsActive())
            tileMap->RemoveTile(mousePosGrid.x, mousePosGrid.y, 0);
    }
    
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

void EditorState::PlayButtonClick()
{
    //states->push(new GameState(states));
}

void EditorState::ExitButtonClick()
{
    quit = true;
}

