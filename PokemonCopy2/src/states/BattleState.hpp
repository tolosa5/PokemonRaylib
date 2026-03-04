#ifndef BATTLESTATE_HPP
#define BATTLESTATE_HPP

#include "src/states/State.hpp"
#include "src/ui/ButtonGroup.hpp"

class BattleState : public State
{
private:

    Rectangle textBox;
    Rectangle attackSelectionBox;
    Rectangle playerInfoBox;
    Rectangle enemyInfoBox;
    Font font;
    
    Texture2D buttonBaseTexture;
    Texture2D buttonHoverTexture;
    Texture2D textBoxTexture;
    Texture2D attackSelectionBoxTexture;
    Texture2D playerInfoBoxTexture;
    Texture2D enemyInfoBoxTexture;

    void BattleButtonClick();
    void BagButtonClick();
    void PkmnButtonClick(bool postFeinted = false);
    void RunButtonClick();
    void Attack1ButtonClick();
    void Attack2ButtonClick();
    void Attack3ButtonClick();
    void Attack4ButtonClick();

public:
    std::map<std::string, Button*> buttons;
    ButtonGroup* buttonGroup;
    std::vector<Button*> buttonVector;

    BattleState(std::stack<State*>* states, float gridSize);
    virtual ~BattleState();

    void InitTextures();
    void InitPlayer();
    void InitFonts();
    void InitButtons();

    void Update(float deltaTime) override;
    void Draw() override;

    void DrawButtons();
    void UpdateButtons();
    void UpdateGui();
    void UpdateBattleInputs();

    void UpdateInputs(float deltaTime) override;
};

#endif