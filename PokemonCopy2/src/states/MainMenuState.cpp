#include "MainMenuState.hpp"
#include "src/ui/ButtonGroup.hpp"

MainMenuState::MainMenuState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    font = LoadFont("assets/fonts/monogram.ttf");
    customFontLoaded = font.texture.id > 0;
    if (!customFontLoaded)
    {
        TraceLog(LOG_WARNING,
            "MAIN_MENU: Failed to load font assets/fonts/monogram.ttf. Using default font.");
        font = GetFontDefault();
    }

    InitTextures();
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

    if (playButtonBaseTexture.id > 0)
        UnloadTexture(playButtonBaseTexture);
    if (playButtonHoverTexture.id > 0)
        UnloadTexture(playButtonHoverTexture);
    if (settingsButtonBaseTexture.id > 0)
        UnloadTexture(settingsButtonBaseTexture);
    if (settingsButtonHoverTexture.id > 0)
        UnloadTexture(settingsButtonHoverTexture);
    if (customFontLoaded)
        UnloadFont(font);
}

void MainMenuState::InitTextures()
{
    playButtonBaseTexture = LoadTexture(
        "assets/graphics/sprites/ui/UnselectedContinueGameBox.png");
    playButtonBaseTexture.width = 700;
    playButtonBaseTexture.height = 273;

    playButtonHoverTexture = LoadTexture(
        "assets/graphics/sprites/ui/HoverContinueGameBox.png");
    playButtonHoverTexture.width = 700;
    playButtonHoverTexture.height = 273;

    settingsButtonBaseTexture = LoadTexture(
        "assets/graphics/sprites/ui/UnselectedOptionsBox.png");
    settingsButtonBaseTexture.width = 200;
    settingsButtonBaseTexture.height = 78;

    settingsButtonHoverTexture = LoadTexture(
        "assets/graphics/sprites/ui/HoverOptionsBox.png");
    settingsButtonHoverTexture.width = 200;
    settingsButtonHoverTexture.height = 78;
}

void MainMenuState::InitBackground()
{
    bgRect = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
}

void MainMenuState::InitButtons()
{
    Rectangle playButtonRect = {(float)(
        GetScreenWidth() / 2.0f - playButtonBaseTexture.width / 2.0f), 
        100, 100, 100};
    float spacing = 50.0f;
    Rectangle settingsButtonRect = {(float)(
        GetScreenWidth() / 2.0f - settingsButtonBaseTexture.width / 2.0f), 
        playButtonRect.y + playButtonRect.height + spacing, 
        25, 25};

    buttons["GAME_STATE_BUTTON"] = new Button(playButtonRect, "Play",
         &font, playButtonBaseTexture, playButtonHoverTexture);
    buttons["GAME_STATE_BUTTON"]->onClick.Subscribe(
        [&]() {
            PlayButtonClick(); });
    buttonVector.push_back(buttons["GAME_STATE_BUTTON"]);

    buttons["SETTINGS_BUTTON"] = new Button(settingsButtonRect, "Settings",
         &font, settingsButtonBaseTexture, settingsButtonHoverTexture);
    buttonVector.push_back(buttons["SETTINGS_BUTTON"]);
    
    buttons["EDITOR_BUTTON"] = new Button({360, settingsButtonRect.y + settingsButtonBaseTexture.height + spacing, 25, 25}, "Editor",
         &font, settingsButtonBaseTexture, settingsButtonHoverTexture);
    buttons["EDITOR_BUTTON"]->onClick.Subscribe(
        [&]() {
            EditorButtonClick(); });
    buttonVector.push_back(buttons["EDITOR_BUTTON"]);

    buttons["EXIT_BUTTON"] = new Button({360, settingsButtonRect.y + settingsButtonBaseTexture.height + spacing * 2, 25, 25}, "Exit",
         &font, settingsButtonBaseTexture, settingsButtonHoverTexture);
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
    DrawRectangleRec(bgRect, Utils::GreyBgColor());
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