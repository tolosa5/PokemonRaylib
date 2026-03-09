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

    player->onEntityMove.Subscribe(
        [&](Vector2 position, Vector2 direction, Entity* entity) {
            CheckEntityCollision(position, direction, entity);
        });

    player->onPlayerInteraction.Subscribe(
        [&](Vector2 targetPos) {
            CheckInteraction(targetPos);
        });

    player->onPlayerMove.Subscribe(
        [&](Vector2 targetPos) {
            CheckPlayerMove(targetPos);
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

    std::cout << "Checking collision at: " << targetPos.x << 
        ", " << targetPos.y << std::endl;

    if (tileMap->GetMap()[targetTileX][targetTileY][0]->HasCollision())
        entity->SetCanMove(false);
    else
        entity->SetCanMove(true);
    
}

void GameState::CheckPlayerMove(Vector2 targetPos)
{
    int targetTileX = targetPos.x / Utils::TILE_SIZE();
    int targetTileY = targetPos.y / Utils::TILE_SIZE();

    std::cout << "Player moved to: " << targetPos.x << 
        ", " << targetPos.y << std::endl;

    Tile* tile = tileMap->GetMap()[targetTileX][targetTileY][0];
    if (tile->GetType() == TileType::GRASS)
        player->SetCanMove(false);
    else if (tile->GetType() == TileType::AREA_CHANGE)
        player->SetCanMove(true);
}

void GameState::CheckInteraction(Vector2 targetPos)
{
    int targetTileX = targetPos.x / Utils::TILE_SIZE();
    int targetTileY = targetPos.y / Utils::TILE_SIZE();

    Tile* tile = tileMap->GetMap()[targetTileX][targetTileY][0];
    if (tile->GetType() == TileType::INTERACTABLE)
    {
        PokeballTile* pokeballTile = static_cast<PokeballTile*>(tile);
        pokeballTile->Interact();
    }  
    else
    {
        for (IInteractable* interactable : interactables)
        {
            bool collision = CheckCollisionPointRec(targetPos, 
                interactable->GetCollider()->collider);
            if (collision && interactable->IsInteractable())
            {
                interactable->Interact();
                return;
            }
        }
    }
        
}

void GameState::AreaChange()
{
    //area change
}

void GameState::StartWildBattle(Pokemon& wildPokemon)
{
    states->push(new BattleState(states, gridSize, player->GetParty(), 
        std::vector<Pokemon>{wildPokemon}, BattleType::WILD));
}

void GameState::StartTrainerBattle(std::vector<Pokemon>& trainerParty)
{
    states->push(new BattleState(states, gridSize, player->GetParty(), 
        trainerParty, BattleType::TRAINER));
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
