class IInteractable
{
public:
    virtual void Interact() = 0;

    bool interactable = true;
    bool IsInteractable() const { return interactable; }
};