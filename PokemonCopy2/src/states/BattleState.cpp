#include "BattleState.hpp"

void BattleState::InitTextures()
{
    buttonBaseTexture = LoadTexture(
        "assets/graphics/sprites/ui/UnselectedButton.png");
    buttonHoverTexture = LoadTexture(
        "assets/graphics/sprites/ui/SelectedButton.png");
    textBoxTexture = LoadTexture(
        "assets/graphics/sprites/ui/TextBoxWide.png");
    playerInfoBoxTexture = LoadTexture(
        "assets/graphics/sprites/ui/PlayerBattleHud.png");
    enemyInfoBoxTexture = LoadTexture(
        "assets/graphics/sprites/ui/EnemyBattleHud.png");
    attackSelectionBoxTexture = LoadTexture(
        "assets/graphics/sprites/ui/AttackSelectionBox.png");
}

void BattleState::InitPlayer()
{

}

void BattleState::InitFonts()
{
    font = LoadFont("assets/fonts/monogram.ttf");
}

void BattleState::InitButtons()
{

}

BattleState::BattleState(std::stack<State*>* states, float gridSize) : 
    State(states, gridSize)
{
    InitTextures();
    InitPlayer();
    InitFonts();
    InputManager::SetCurrentMode(UI);
}

BattleState::~BattleState()
{

}

void BattleState::Update(float deltaTime)
{
    UpdateButtons();
    UpdateGui();
    UpdateBattleInputs();
}

void BattleState::Draw()
{
    DrawButtons();
}

void BattleState::DrawButtons()
{

}

void BattleState::UpdateButtons()
{

}

void BattleState::UpdateGui()
{

}

void BattleState::UpdateBattleInputs()
{

}

void BattleState::UpdateInputs(float deltaTime)
{
    UpdateMousePositions();
    UpdateBattleInputs();
}