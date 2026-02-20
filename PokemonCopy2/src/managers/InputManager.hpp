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
    // Private constructor for singleton pattern
    InputManager() {}

public:
    // Delete copy constructor and assignment operator
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    // Static method to get the singleton instance
    static InputManager& GetInstance()
    {
        static InputManager instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }
};

#endif