#include "EditorState.hpp"

EditorState::EditorState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    font = LoadFont("assets/fonts/monogram.ttf");

    InitBackground();
    InitTexts();
    InitTileMap();
    InitGui();

    selectedSheetTile = { 0, 0 };
    paintedRect = { 0, 0, gridSize, gridSize };

    paintedTileCollision = false;
    paintedTileType = TileType::DEFAULT;
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
    InitButtons();
    selectorRect = { 0, 0, gridSize, gridSize };
    textureSelector = new TextureSelector(
        { 64, 32 }, { 256, 600 }, gridSize, tileMap->GetTextureSheet(), font);
    
    sideBarRect = { 0, 0, 64, static_cast<float>(GetScreenHeight()) };
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
    tileMap = new TileMap(gridSize, 20, 20, "assets/graphics/sprites/tileset.png");
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
    DrawRectangleRec(sideBarRect, ColorAlpha(DARKGRAY, 0.5f));
    DrawRectangleLinesEx(sideBarRect, 2, BLACK);

    //Cursor text
    DrawText(cursorText.c_str(), GetMousePosition().x + 10, 
        GetMousePosition().y, 8, WHITE);

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

    std::stringstream ss;
    ss << GetMousePosition().x << " " << GetMousePosition().y << 
     "\n" << mousePosGrid.x << " " << mousePosGrid.y <<
        "\n" << paintedRect.x << " " << paintedRect.y <<
        "\n" << "Collision: " << paintedTileCollision <<
        "\n" << "Type: " << paintedTileType;

    cursorText = ss.str();
}

void EditorState::UpdateEditorInputs()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (!textureSelector->IsActive() && !CheckCollisionRecs(selectorRect, sideBarRect))
            tileMap->AddTile(mousePosGrid.x, mousePosGrid.y, 0, 
                paintedRect, paintedTileCollision, paintedTileType);
        else
            paintedRect = textureSelector->GetSelectedRect();
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (!textureSelector->IsActive() && !CheckCollisionRecs(selectorRect, sideBarRect))
            tileMap->RemoveTile(mousePosGrid.x, mousePosGrid.y, 0);
    }

    else if (IsKeyPressed(KEY_TAB))
        textureSelector->SetHidden(!textureSelector->IsHidden());

    else if (IsKeyPressed(KEY_S))
        tileMap->SaveToFile("text.slmp");
    else if (IsKeyPressed(KEY_L))
        tileMap->LoadFromFile("text.slmp");

    else if (IsKeyPressed(KEY_C))
        paintedTileCollision = !paintedTileCollision;
    else if (IsKeyPressed(KEY_UP))
    {
        if (paintedTileType + 1 >= TileType::COUNT)
            return;
        paintedTileType++;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        if (paintedTileType <= 0)
            return;
        paintedTileType--;
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

