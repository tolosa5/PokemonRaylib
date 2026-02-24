#ifndef POKEDEXPANEL_HPP
#define POKEDEXPANEL_HPP

#include "src/ui/PausePanels/Panel.hpp"

class PokedexPanel : public Panel
{
private:

public:
    PokedexPanel() = default;
    virtual ~PokedexPanel() = default;

    void Update() override {}
    void Draw() override {}
};

#endif