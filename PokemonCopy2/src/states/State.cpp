#include "src/states/State.hpp"
#include "State.hpp"

State::State(std::stack<State*>* states, float gridSize)
{
    this->states = states;
    this->gridSize = gridSize;
    quit = false;
}

State::~State()
{

}

void State::EndState()
{
    quit = true;
}

void State::UpdateMousePositions()
{
    Vector2 mousePos = GetMousePosition();
    mousePosGrid.x = static_cast<int>(mousePos.x / gridSize);
    mousePosGrid.y = static_cast<int>(mousePos.y / gridSize);
}