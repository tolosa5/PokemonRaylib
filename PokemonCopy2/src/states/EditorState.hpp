#ifndef EDITORSTATE_HPP
#define EDITORSTATE_HPP

#include "src/states/State.hpp"
#include "src/ui/Button.hpp"
#include "src/map/TileMap.hpp"

class EditorState : public State
{
private:

    Rectangle selectorRect;
    Texture2D backgroundTexture;
    Font font;

    std::map<std::string, Button*> buttons;
    //ButtonGroup* buttonGroup;
    std::vector<Button*> buttonVector;

    TileMap* tileMap;

    void InitBackground();
    void InitGui();
    void InitButtons();
    void InitTileMap();

protected:
    

public:
    EditorState(std::stack<State*>* states, float gridSize);
    virtual ~EditorState();

    void Update(float deltaTime) override;
    void Draw() override;

    void DrawButtons();
    void UpdateButtons();
    void UpdateGui();
    void UpdateEditorInputs();
    
    void PlayButtonClick();
    void ExitButtonClick();

    void UpdateInputs(float deltaTime) override;

};

#endif