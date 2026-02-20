#include "ButtonGroup.hpp"

ButtonGroup::ButtonGroup(std::vector<Button*>& buttons, GroupMode mode) : 
    buttons(buttons)
{
    this->mode = mode;
}

void ButtonGroup::Update()
{
    
}

void ButtonGroup::Draw()
{
    for (Button* button : buttons)
    {
        if (button)
            button->Draw();
    }
}

void ButtonGroup::ButtonsIteration()
{
    switch (mode)
    {
        case VERTICAL:
        {
            if (IsKeyPressed(KEY_DOWN))
            {
                Button* hoveredButton = GetHoveredButton();
                if (!hoveredButton)
                    return;
                
                hoveredButton->SetButtonState(IDLE);
                for (int i = 0; i < buttons.size(); ++i)
                {
                    if (buttons[i] == hoveredButton)
                    {
                        if (i + 1 < buttons.size())
                        {
                            buttons[i + 1]->SetButtonState(HOVER);
                            hoveredButton = buttons[i + 1];
                        }
                        else
                        {
                            buttons[0]->SetButtonState(HOVER);
                            hoveredButton = buttons[0];
                        }
                        break;
                    }
                }
            }
            break;
        }

        case HORIZONTAL:
        {
            if (IsKeyPressed(KEY_RIGHT))
            {
                Button* hoveredButton = GetHoveredButton();
                if (!hoveredButton)
                    return;
                
                hoveredButton->SetButtonState(IDLE);
                for (int i = 0; i < buttons.size(); ++i)
                {
                    if (buttons[i] == hoveredButton)
                    {
                        if (i + 1 < buttons.size())
                        {
                            buttons[i + 1]->SetButtonState(HOVER);
                            hoveredButton = buttons[i + 1];
                        }
                        else
                        {
                            buttons[0]->SetButtonState(HOVER);
                            hoveredButton = buttons[0];
                        }
                        break;
                    }
                }
            }

            if (IsKeyPressed(KEY_LEFT))
            {
                Button* hoveredButton = GetHoveredButton();
                if (!hoveredButton)
                    return;
                
                hoveredButton->SetButtonState(IDLE);
                for (int i = 0; i < buttons.size(); ++i)
                {
                    if (buttons[i] == hoveredButton)
                    {
                        if (i - 1 >= 0)
                        {
                            buttons[i - 1]->SetButtonState(HOVER);
                            hoveredButton = buttons[i - 1];
                        }
                        else
                        {
                            buttons[buttons.size() - 1]->SetButtonState(HOVER);
                            hoveredButton = buttons[buttons.size() - 1];
                        }
                        break;
                    }
                }
            }
            
            break;
        }
    }
}

Button* ButtonGroup::GetHoveredButton() const
{
    for (Button* button : buttons)
    {
        if (button && button->IsHovered())
            return button;
    }
    return nullptr;
}