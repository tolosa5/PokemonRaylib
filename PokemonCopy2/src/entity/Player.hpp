#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include <vector>
#include "src/core/pokemonCore/Pokemon.hpp"
#include "Entity.hpp"

class Player : public Entity
{
private:
    bool isRunning;
    Vector2 interactPoint;

    void InitVariables();
    void InitComponents(Texture2D& texture);

public:
    std::vector<Pokemon> party;
    Event<const Pokemon&> onPokemonAdded;
    Event<Vector2> onPlayerInteraction;
    Event<Vector2> onPlayerMove;


    Player(Texture2D& texture, Vector2 position);
    virtual ~Player();

    void Update(float deltaTime) override;
    void Draw() override;
    void Move(const Vector2 direction) override;
    void LoadAnimations();
    void Interact();
    void OpenMenu();
    void ToggleRun() { isRunning = !isRunning; }
    void AddPokemonToParty(Pokemon pokemon);

    MovementComponent* GetMovementComponent() const { 
        return movementComponent; }
    std::vector<Pokemon>& GetParty() { return party; }
};

#endif 