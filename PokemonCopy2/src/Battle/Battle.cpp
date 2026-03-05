#include "Battle.hpp"

void Battle::InitButtons()
{

}

Battle::Battle(std::vector<Pokemon> playerParty, std::vector<Pokemon> enemyParty) : 
    playerParty(playerParty), enemyParty(enemyParty)
{
    BattleStart();
}

Battle::~Battle()
{
    
}

void Battle::BattleStart()
{
    playerUnit.SetUp(&this->playerParty[0], true);
    enemyUnit.SetUp(&this->enemyParty[0], false);
}

void Battle::PokemonFeinted(Pokemon& faintedPokemon)
{
    OpenPkmnTab(true);
}

void Battle::ChangePokemon(Pokemon& newPokemon)
{
    playerUnit.SetUp(&newPokemon, true);
}

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