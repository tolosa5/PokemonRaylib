#include "src/states/GameState.hpp"

void GameState::InitTextures()
{
    Texture2D playerTexture = LoadTexture("assets/graphics/sprites/player/player.png");
    textures["PLAYER_IDLE"] = playerTexture;
    InitPlayer();
    //player->SetPosition({100, 100});
}

void GameState::InitPlayer()
{
    player = new Player(textures["PLAYER_IDLE"], {100, 100});
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

    if (IsKeyPressed(KEY_UP)) 
    {
        dir.y = -1;
        dir.x = 0;
    }
    else if (IsKeyPressed(KEY_DOWN))  
    {
        dir.y =  1;
        dir.x = 0;
    }
    else if (IsKeyPressed(KEY_LEFT))  
    {
        dir.x = -1;
        dir.y = 0;
    }
    else if (IsKeyPressed(KEY_RIGHT)) 
    {
        dir.x =  1;
        dir.y = 0;
    }

    if (dir.x != 0 || dir.y != 0)
    {
        player->Move(dir);
    }

    if (IsKeyPressed(KEY_ESCAPE))
        EndState();
    
}
