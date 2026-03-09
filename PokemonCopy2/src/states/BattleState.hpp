#ifndef BATTLESTATE_HPP
#define BATTLESTATE_HPP

#include "src/states/State.hpp"
#include "src/ui/ButtonGroup.hpp"
#include "src/Battle/Battle.hpp"

class BattleState : public State
{
private:

    Font font;

    std::vector<Pokemon> playerParty;
    std::vector<Pokemon> enemyParty;
    Battle* battle;
    BattleType battleType;
    
    void BattleButtonClick();
    void BagButtonClick();
    void PkmnButtonClick(bool postFainted = false);
    void RunButtonClick();
    void Attack1ButtonClick();
    void Attack2ButtonClick();
    void Attack3ButtonClick();
    void Attack4ButtonClick();

public:
    
    BattleState(std::stack<State*>* states, int gridSize, std::vector<Pokemon> playerParty, 
        std::vector<Pokemon> enemyParty, BattleType battleType);
    virtual ~BattleState();

    void InitTextures();
    void InitPlayer();
    void InitFonts();
    void InitButtons();

    void Update(float deltaTime) override;
    void Draw() override;

    void NewBattle();
    void DrawButtons();
    void UpdateButtons();
    void UpdateGui();
    void UpdateBattleInputs();

    void UpdateInputs(float deltaTime) override;
};

#endif