#include "BattleState.hpp"

void BattleState::InitTextures()
{
    battle->battleUI.buttonBaseTexture = LoadTexture(
        "assets/graphics/sprites/ui/UnselectedButton.png");
    battle->battleUI.buttonHoverTexture = LoadTexture(
        "assets/graphics/sprites/ui/SelectedButton.png");
    battle->battleUI.textBoxTexture = LoadTexture(
        "assets/graphics/sprites/ui/TextBoxWide.png");
    battle->battleUI.playerHudTexture = LoadTexture(
        "assets/graphics/sprites/ui/PlayerBattleHud.png");
    battle->battleUI.enemyHudTexture = LoadTexture(
        "assets/graphics/sprites/ui/EnemyBattleHud.png");
    battle->battleUI.attackSelectionBoxTexture = LoadTexture(
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
    #pragma region Start Buttons

    battle->buttons["Battle"] = new Button({ 10, 400, 150, 50 }, 
        "Battle", &font, battle->battleUI.buttonBaseTexture, battle->battleUI.buttonHoverTexture);
    battle->buttons["Battle"]->onClick.Subscribe(
        [this]() { battle->BattleButtonClick(); });
    battle->startButtonVector.push_back(battle->buttons["Battle"]);

    battle->buttons["Bag"] = new Button({ 170, 400, 150, 50 }, 
        "Bag", &font, battle->battleUI.buttonBaseTexture, battle->battleUI.buttonHoverTexture);
    battle->buttons["Bag"]->onClick.Subscribe(
        [this]() { battle->BagButtonClick(); });
    battle->startButtonVector.push_back(battle->buttons["Bag"]);

    battle->buttons["Pkmn"] = new Button({ 330, 400, 150, 50 }, 
        "Pkmn", &font, battle->battleUI.buttonBaseTexture, battle->battleUI.buttonHoverTexture);
    battle->buttons["Pkmn"]->onClick.Subscribe(
        [this]() { battle->OpenPkmnTab(); });
    battle->startButtonVector.push_back(battle->buttons["Pkmn"]);

    battle->buttons["Run"] = new Button({ 490, 400, 150, 50 }, 
        "Run", &font, battle->battleUI.buttonBaseTexture, battle->battleUI.buttonHoverTexture);
    battle->buttons["Run"]->onClick.Subscribe(
        [this]() { battle->RunButtonClick(); });
    battle->startButtonVector.push_back(battle->buttons["Run"]);

    battle->startButtonGroup = new ButtonGroup(battle->startButtonVector, GRID, 2, 2);
    battle->startButtonGroup->SetActive(false);

    #pragma endregion

    #pragma region Battle Buttons

    battle->buttons["MoveTL"] = new Button({ 10, 400, 150, 50 }, 
        "Attack1", &font, battle->battleUI.buttonBaseTexture, 
        battle->battleUI.buttonHoverTexture);
    battle->buttons["MoveTL"]->onClick.Subscribe(
        [this]() { battle->Attack1ButtonClick(); });
    battle->battleButtonVector.push_back(battle->buttons["MoveTL"]);

    battle->buttons["MoveTR"] = new Button({ 170, 400, 150, 50 }, 
        "Attack2", &font, battle->battleUI.buttonBaseTexture, 
        battle->battleUI.buttonHoverTexture);
    battle->buttons["MoveTR"]->onClick.Subscribe(
        [this]() { battle->Attack2ButtonClick(); });
    battle->battleButtonVector.push_back(battle->buttons["MoveTR"]);

    battle->buttons["MoveBL"] = new Button({ 10, 400, 150, 50 }, 
        "Attack3", &font, battle->battleUI.buttonBaseTexture, 
        battle->battleUI.buttonHoverTexture);
    battle->buttons["MoveBL"]->onClick.Subscribe(
        [this]() { battle->Attack3ButtonClick(); });
    battle->battleButtonVector.push_back(battle->buttons["MoveBL"]);

    battle->buttons["MoveBR"] = new Button({ 170, 400, 150, 50 }, 
        "Attack4", &font, battle->battleUI.buttonBaseTexture, 
        battle->battleUI.buttonHoverTexture);
    battle->buttons["MoveBR"]->onClick.Subscribe(
        [this]() { battle->Attack4ButtonClick(); });
    battle->battleButtonVector.push_back(battle->buttons["MoveBR"]);

    battle->battleButtonGroup = new ButtonGroup(battle->battleButtonVector, GRID, 2, 2);
    battle->battleButtonGroup->SetActive(false);
    #pragma endregion
}

BattleState::BattleState(std::stack<State*>* states, int gridSize, 
    std::vector<Pokemon> playerParty, std::vector<Pokemon> enemyParty, 
    BattleType battleType) : 
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
    battle = new Battle(playerParty, enemyParty, battleType, font);
}

void BattleState::DrawButtons()
{
    battle->startButtonGroup->Draw();
    battle->battleButtonGroup->Draw();

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