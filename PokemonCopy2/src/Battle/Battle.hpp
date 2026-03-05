#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "src/ui/ButtonGroup.hpp"
#include "BattleUnit.hpp"
#include <map>
#include <vector>

class Battle
{
public:
    BattleUnit playerUnit;
    BattleUnit enemyUnit;

    std::vector<Pokemon> playerParty;
    std::vector<Pokemon> enemyParty;

    Battle(std::vector<Pokemon> playerParty, 
        std::vector<Pokemon> enemyParty);
    ~Battle();

    void BattleStart();

private:
    
    void InitButtons();

    void PokemonFeinted(Pokemon& faintedPokemon);
    void ChangePokemon(Pokemon& newPokemon);

    void BattleButtonClick();
    void BagButtonClick();
    void OpenPkmnTab(bool postFeinted = false);
    void RunButtonClick();
    void Attack1ButtonClick();
    void Attack2ButtonClick();
    void Attack3ButtonClick();
    void Attack4ButtonClick();

};

#endif