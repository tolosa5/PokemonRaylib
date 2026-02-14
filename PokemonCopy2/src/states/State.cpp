#include "src/states/State.hpp"
#include "State.hpp"

State::State(std::map<std::string, int>* supportedKeys)
{
    this->supportedKeys = supportedKeys;
    quit = false;
}

State::~State()
{

}

void State::CheckForQuit()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        quit = true;
    }
}