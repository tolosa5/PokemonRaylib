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
    MovementComponent* playerMovementComponent = player->GetMovementComponent();

    if (playerMovementComponent->moving)
        return;

    Vector2 dir = {0, 0};
    playerMovementComponent->direction = dir;

    if (IsKeyDown(KEY_W)) 
    {
        dir.y = -1;
        dir.x = 0;
    }
    if (IsKeyDown(KEY_S))  
    {
        dir.y = 1;
        dir.x = 0;
    }
    if (IsKeyDown(KEY_A))  
    {
        dir.x = -1;
        dir.y = 0;
    }
    if (IsKeyDown(KEY_D)) 
    {
        dir.x = 1;
        dir.y = 0;
    }

    if (dir.x != 0 || dir.y != 0)
    {
        player->Move(dir);
        playerMovementComponent->lastDirection = dir;
    }

    if (IsKeyPressed(KEY_ESCAPE))
        EndState();
}
