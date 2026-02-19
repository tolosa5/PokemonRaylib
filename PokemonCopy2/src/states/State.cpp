#include "src/states/State.hpp"
#include "State.hpp"

State::State(std::stack<State*>* states)
{
    this->states = states;
    quit = false;
}

State::~State()
{

}

void State::CheckForQuit()
{
    if (IsKeyPressed(KEY_ESCAPE))
        quit = true;
}