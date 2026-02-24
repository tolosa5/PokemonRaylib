#ifndef POKEMONPANEL_HPP
#define POKEMONPANEL_HPP

#include "src/ui/PausePanels/Panel.hpp"

class PokemonPanel : public Panel
{
private:

public:
    PokemonPanel() = default;
    virtual ~PokemonPanel() = default;

    void Update() override {}
    void Draw() override {}
};

#endif