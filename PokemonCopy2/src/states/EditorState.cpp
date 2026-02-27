#include "EditorState.hpp"

EditorState::EditorState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    font = LoadFont("assets/fonts/monogram.ttf");

    InitBackground();
    InitButtons();
    InitTileMap();
    InitGui();
    InitTexts();

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
    DrawButtons();
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
    int selectedX = static_cast<int>(selectedSheetTile.x);
    int selectedY = static_cast<int>(selectedSheetTile.y);

    const int maxColumns = static_cast<int>(tileMap->GetSheetColumns(gridSize));
    const int maxRows = static_cast<int>(tileMap->GetSheetRows(gridSize));

    if (IsKeyPressed(KEY_RIGHT))
        selectedX++;
    if (IsKeyPressed(KEY_LEFT))
        selectedX--;
    if (IsKeyPressed(KEY_DOWN))
        selectedY++;
    if (IsKeyPressed(KEY_UP))
        selectedY--;

    selectedX = Clamp(selectedX, 0, maxColumns - 1);
    selectedY = Clamp(selectedY, 0, maxRows - 1);

    selectedSheetTile = {
        static_cast<float>(selectedX),
        static_cast<float>(selectedY)
    };

    paintedRect.x = selectedSheetTile.x * gridSize;
    paintedRect.y = selectedSheetTile.y * gridSize;
    paintedRect.width = gridSize;
    paintedRect.height = gridSize;


    selectorRect.x = mousePosGrid.x * gridSize;
    selectorRect.y = mousePosGrid.y * gridSize;
}

void EditorState::UpdateEditorInputs()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        tileMap->AddTile(mousePosGrid.x, mousePosGrid.y, 0, paintedRect);
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
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

