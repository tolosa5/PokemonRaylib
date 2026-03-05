#include "src/states/GameState.hpp"

#pragma region Initialization

void GameState::InitTextures()
{
    Texture2D playerTexture = LoadTexture(
        "assets/graphics/sprites/player/PlayerSheet.png");
    textures["PLAYER_SHEET"] = playerTexture;
    InitPlayer();
}

void GameState::InitPlayer()
{
    player = new Player(textures["PLAYER_SHEET"], 
        {(float)(GetScreenWidth() / 2), 
            (float)(GetScreenHeight() / 2)});

    player->onMove.Subscribe(
        [&](Vector2 position, Vector2 direction, Entity* entity) {
            CheckEntityCollision(position, direction, entity);
        });

    player->onPlayerInteraction.Subscribe(
        [&](Vector2 targetPos) {
            CheckInteraction(targetPos);
        });
}

void GameState::InitFonts()
{
    font = LoadFont("assets/graphics/fonts/PokemonFont.ttf");
}

void GameState::InitPauseMenu()
{
    pauseMenu = new PauseMenu(font);
}

void GameState::InitTileMap()
{
    tileMap = new TileMap(gridSize, 10, 10, "assets/graphics/sprites/tileset.png");
}

#pragma endregion

GameState::GameState(std::stack<State*>* states, float gridSize) 
    : State(states, gridSize)
{
    InitTextures();
    InitFonts();
    InitPauseMenu();
    InitTileMap();
    InputManager::SetCurrentMode(GAMEPLAY);
    isPaused = false;
}

GameState::~GameState()
{
    delete player;
    delete pauseMenu;
    delete tileMap;
}

void GameState::Update(float deltaTime)
{
    if (isPaused)
        pauseMenu->Update();
    else
    {
        UpdateInputs(deltaTime);
        player->Update(deltaTime);
    }
}

void GameState::Draw()
{
    if (isPaused)
        pauseMenu->Draw();
    
    player->Draw();
}

void GameState::UpdateInputs(float deltaTime)
{
    if (IsKeyPressed(KEY_ESCAPE))
        EndState();

    switch (InputManager::GetCurrentMode())
    {
    default:
    case GAMEPLAY:
        UpdateGameplayInputs(deltaTime);
        break;
    case UI:
        UpdateUIInputs(deltaTime);
        break;
    }
}

void GameState::UpdateGameplayInputs(float deltaTime)
{
    if (IsKeyPressed(KEY_C))
        player->Interact();
    
    if (IsKeyPressed(KEY_D))
        OpenPauseMenu();
    
    if (IsKeyPressed(KEY_X))
        player->ToggleRun();
    
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
    pauseMenu->UpdateInputs();
    if (IsKeyPressed(KEY_X))
        ClosePauseMenu();
}

void GameState::CheckEntityCollision(Vector2 position, Vector2 targetPos, Entity* entity)
{
    int targetTileX = targetPos.x / Utils::TILE_SIZE();
    int targetTileY = targetPos.y / Utils::TILE_SIZE();

    if (tileMap->GetMap()[targetTileX][targetTileY][0]->HasCollision())
        entity->SetCanMove(false);
    else
        entity->SetCanMove(true);
    
}

void GameState::CheckInteraction(Vector2 targetPos)
{
    int targetTileX = targetPos.x / Utils::TILE_SIZE();
    int targetTileY = targetPos.y / Utils::TILE_SIZE();

    if (tileMap->GetMap()[targetTileX][targetTileY][0]->
        GetType() == TileType::INTERACTABLE)
    {
        
    }  
    else
    {
        for (IInteractable* interactable : interactables)
        {
            if (CheckCollisionPointRec(targetPos, interactable->
                GetCollider()->collider) && 
                interactable->IsInteractable())
            {
                interactable->Interact();
                return;
            }
        }
    }
        
}

void GameState::OpenPauseMenu()
{
    if (isPaused)
        ClosePauseMenu();
    else
    {
        InputManager::SetCurrentMode(UI);
        isPaused = true;
    }
}

void GameState::ClosePauseMenu()
{
    InputManager::SetCurrentMode(GAMEPLAY);
    isPaused = false;
}
