#include "Battle.hpp"

void Battle::InitButtons()
{

}

Battle::Battle(std::vector<Pokemon> playerParty, 
    std::vector<Pokemon> enemyParty, BattleType battleType)
{
    this->playerParty = playerParty;
    this->enemyParty = enemyParty;
    this->currentBattleType = battleType;
    BattleStart();
}

Battle::~Battle()
{
    
}

void Battle::BattleStart()
{
    this->currentBattleState = BattleState::START;

    playerUnit.SetUp(&this->playerParty[0], true);
    enemyUnit.SetUp(&this->enemyParty[0], false);
}

void Battle::Update()
{

}

void Battle::Draw()
{
    switch (currentBattleState)
    {
    case BattleState::NONE:
        /* code */
        break;

    case BattleState::START:
        /* code */
        break;

    case BattleState::PLAYER_TURN:
        /* code */
        break;

    case BattleState::ENEMY_TURN:
        /* code */
        break;

    case BattleState::BUSY:
        /* code */
        break;

    case BattleState::WON:
        /* code */
        break;

    case BattleState::LOST:
        /* code */
        break;

    default:
        break;
    }
}

#pragma region Battle Logic

void Battle::ChangePokemon(Pokemon& newPokemon)
{
    playerUnit.SetUp(&newPokemon, true);
}

void Battle::HandlePlayerTurn()
{
    
}

void Battle::HandleEnemyTurn()
{

}

void Battle::DamageHandling(Pokemon& attacker, Pokemon& target, 
    Move& move, bool isPlayerAttacking)
{
    DamageDetails details = target.TakeDamage(move, attacker);
    
    if (details.critical)
        std::cout << "A critical hit!" << std::endl;
    if (details.typeEffectiveness > 1.0f)
        std::cout << "It's super effective!" << std::endl;
    else if (details.typeEffectiveness < 1.0f)
        std::cout << "It's not very effective..." << std::endl;
    if (details.fainted)
    {
        if (isPlayerAttacking)
            PlayerPokemonFainted(target);
        else
            EnemyPokemonFainted(target);
    }
}

void Battle::PlayerPokemonFainted(Pokemon& faintedPokemon)
{
    OpenPkmnTab(true);
}

void Battle::EnemyPokemonFainted(Pokemon& faintedPokemon)
{
    // Handle enemy Pokemon fainting
}

void Battle::EndBattle(EndBattleReason endReason)
{
    switch (endReason)
    {
    case EndBattleReason::PLAYER_FLED:
        // Handle player fleeing
        break;

    case EndBattleReason::PLAYER_WON:
        // Handle player victory
        break;

    case EndBattleReason::ENEMY_WON:
        // Handle enemy victory
        break;

    default:
        break;
    }

    // Clean up battle and return to previous state
}

#pragma endregion

#pragma region Button Clicks

void Battle::BattleButtonClick()
{

}

void Battle::BagButtonClick()
{

}

void Battle::OpenPkmnTab(bool postFeinted)
{

}

void Battle::RunButtonClick()
{
    if (currentBattleType == BattleType::TRAINER)
        return;
    
    EndBattleReason reason = EndBattleReason::PLAYER_FLED;
    EndBattle(reason);
}

void Battle::Attack1ButtonClick()
{

}

void Battle::Attack2ButtonClick()
{

}

void Battle::Attack3ButtonClick()
{

}

void Battle::Attack4ButtonClick()
{

}

#pragma endregion