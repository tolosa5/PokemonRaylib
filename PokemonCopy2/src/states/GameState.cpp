#include "src/states/GameState.hpp"

void GameState::InitTextures()
{
    Texture2D playerTexture = LoadTexture("assets/graphics/sprites/player/PlayerSheet.png");
    textures["PLAYER_SHEET"] = playerTexture;
    InitPlayer();
}

void GameState::InitPlayer()
{
    player = new Player(textures["PLAYER_SHEET"], {100, 100});
}

GameState::GameState(std::stack<State*>* states) : 
    State(states)
{
    InitTextures();
}

GameState::~GameState()
{
    delete player;
}

void GameState::Update(float deltaTime)
{
    UpdateInputs(deltaTime);
    player->Update(deltaTime);
}

void GameState::Draw()
{
    player->Draw();
}

void GameState::UpdateInputs(float deltaTime)
{
    switch (inputManager.GetCurrentMode())
    {
    default:
    case GAMEPLAY:
        UpdateGameplayInputs(deltaTime);
        break;
    case UI:
        UpdateUIInputs(deltaTime);
        break;
        break;
    }
}

void GameState::UpdateGameplayInputs(float deltaTime)
{
    if (IsKeyPressed(KEY_C))
    player->Interact();
    
    if (IsKeyPressed(KEY_D))
    player->OpenMenu();
    
    if (IsKeyPressed(KEY_X))
    player->ToggleRun();
    
    if (IsKeyPressed(KEY_ESCAPE))
    EndState();
    
    MovementComponent* playerMovementComponent = player->GetMovementComponent();
    if (playerMovementComponent->moving)
    return;
    
    Vector2 dir = {0, 0};
    playerMovementComponent->direction = dir;

    if (IsKeyDown(KEY_UP)) 
    {
        dir = {0, -1};
        player->Move(dir);
    }
    else if (IsKeyDown(KEY_DOWN))  
    {
        dir = {0, 1};
        player->Move(dir);
    }
    else if (IsKeyDown(KEY_LEFT))  
    {
        dir = {-1, 0};
        player->Move(dir);
    }
    else if (IsKeyDown(KEY_RIGHT)) 
    {
        dir = {1, 0};
        player->Move(dir);
    }

    if (dir.x != 0 || dir.y != 0)
        playerMovementComponent->lastDirection = dir;
}

void GameState::UpdateUIInputs(float deltaTime)
{
    // Handle UI-specific inputs here
}
