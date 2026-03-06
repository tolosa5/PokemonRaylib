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

BattleState::BattleState(std::stack<State*>* states, std::vector<Pokemon> playerParty, 
    std::vector<Pokemon> enemyParty, BattleType battleType) : 
    State(states, gridSize)
{
    this->playerParty = playerParty;
    this->enemyParty = enemyParty;
    this->battleType = battleType;

    InitTextures();
    InitPlayer();
    InitFonts();
    InputManager::SetCurrentMode(UI);
}

BattleState::~BattleState()
{
    delete battle;
}

void BattleState::Update(float deltaTime)
{
    battle->Update();
    UpdateButtons();
    UpdateGui();
    UpdateBattleInputs();
}

void BattleState::Draw()
{
    battle->Draw();
    DrawButtons();
}

void BattleState::NewBattle()
{
    // Initialize a new battle
    battle = new Battle(playerParty, enemyParty, battleType);
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