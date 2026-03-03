#ifndef EDITORSTATE_HPP
#define EDITORSTATE_HPP

#include "src/states/State.hpp"
#include "src/ui/Button.hpp"
#include "src/map/TileMap.hpp"
#include "src/ui/TextureSelector.hpp"

class EditorState : public State
{
private:

    Rectangle selectorRect;
    Rectangle paintedRect;
    Vector2 selectedSheetTile;
    Texture2D backgroundTexture;
    Font font;
    std::string cursorText;

    std::map<std::string, Button*> buttons;
    //ButtonGroup* buttonGroup;
    std::vector<Button*> buttonVector;

    TileMap* tileMap;
    TextureSelector* textureSelector;

    Rectangle sideBarRect;

    bool paintedTileCollision;
    short paintedTileType;

    void InitBackground();
    void InitGui();
    void InitButtons();
    void InitTileMap();
    void InitTexts();

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