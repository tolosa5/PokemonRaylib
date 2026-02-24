#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

enum InputMode
{
    GAMEPLAY,
    UI
};

class InputManager
{
private:
    static InputMode currentMode;

public:
    InputManager() = default;
    static InputMode GetCurrentMode() { return currentMode; }
    static void SetCurrentMode(InputMode mode) { currentMode = mode; }
};

#endif