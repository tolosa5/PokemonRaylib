#include "ButtonGroup.hpp"

ButtonGroup::ButtonGroup(std::vector<Button*>& buttons, 
    GroupMode mode, int rows, int columns) 
    : buttons(buttons), rows(rows), columns(columns)
{
    this->mode = mode;
    HoverButton(0);
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

void ButtonGroup::GridSetup()
{
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (i == 0)
        {
            leftMargin = buttons[i]->GetRect().x;
            topMargin = buttons[i]->GetRect().y;
            rightMargin = buttons[i]->GetRect().x + buttons[i]->GetRect().width;
            bottomMargin = buttons[i]->GetRect().y + buttons[i]->GetRect().height;
        }
        else
        {
            if (buttons[i]->GetRect().x < leftMargin)
                leftMargin = buttons[i]->GetRect().x;

            if (buttons[i]->GetRect().y < topMargin)
                topMargin = buttons[i]->GetRect().y;
                
            if (buttons[i]->GetRect().x + buttons[i]->GetRect().width > rightMargin)
                rightMargin = buttons[i]->GetRect().x + buttons[i]->GetRect().width;

            if (buttons[i]->GetRect().y + buttons[i]->GetRect().height > bottomMargin)
                bottomMargin = buttons[i]->GetRect().y + buttons[i]->GetRect().height;
        }
        
    }
}

void ButtonGroup::ButtonsIteration()
{
    switch (mode)
    {
        case VERTICAL:
        {
            VerticalIteration();
            break;
        }

        case HORIZONTAL:
        {
            HorizontalIteration();
            break;
        }

        case GRID:
        {
            GridSetup();
            GridIteration();
            break;
        }
    }
}

void ButtonGroup::VerticalIteration()
{
    if (IsKeyPressed(KEY_DOWN))
    {
        Button* hoveredButton = GetHoveredButton();
        if (!hoveredButton)
        {
            buttons[0]->SetButtonState(HOVER);
            return;
        }
                
        hoveredButton->SetButtonState(IDLE);
        for (size_t i = 0; i < buttons.size(); ++i)
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
            }
        }
    }

    if (IsKeyPressed(KEY_UP))
    {
        Button* hoveredButton = GetHoveredButton();
        if (!hoveredButton)
        {
            buttons[0]->SetButtonState(HOVER);
            return;
        }
        
        hoveredButton->SetButtonState(IDLE);
        for (size_t i = 0; i < buttons.size(); ++i)
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
}

void ButtonGroup::HorizontalIteration()
{
    if (IsKeyPressed(KEY_RIGHT))
    {
        Button* hoveredButton = GetHoveredButton();
        if (!hoveredButton)
        {
            buttons[0]->SetButtonState(HOVER);
            return;
        }
                
        hoveredButton->SetButtonState(IDLE);
        for (size_t i = 0; i < buttons.size(); ++i)
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
            }
        }
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        Button* hoveredButton = GetHoveredButton();
        if (!hoveredButton)
        {
            buttons[0]->SetButtonState(HOVER);
            return;
        }
        
        hoveredButton->SetButtonState(IDLE);
        for (size_t i = 0; i < buttons.size(); ++i)
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
}

void ButtonGroup::GridIteration()
{
    if (!IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) && 
        !IsKeyPressed(KEY_RIGHT) && !IsKeyPressed(KEY_LEFT))
        return;

    Button* hoveredButton = GetHoveredButton();
    if (!hoveredButton)
    {
        HoverButton(0);
        return;
    }
            
    hoveredButton->SetButtonState(IDLE);
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i] != hoveredButton)
            continue;

        if (IsKeyPressed(KEY_DOWN))
        {
            if (hoveredButton->GetRect().y >= bottomMargin)
            {
                for (int j = 0; j < buttons.size(); ++j)
                {
                    if (buttons[j]->GetRect().x == hoveredButton->GetRect().x &&
                        buttons[j]->GetRect().y == topMargin)
                    {
                        HoverButton(j);
                        return;
                    }
                }
            }
            
            HoverButton(i + columns);
        }
        else if (IsKeyPressed(KEY_UP))
        {
            if (hoveredButton->GetRect().y <= topMargin)
            {
                for (int j = 0; j < buttons.size(); ++j)
                {
                    if (buttons[j]->GetRect().x == hoveredButton->GetRect().x &&
                        buttons[j]->GetRect().y == bottomMargin)
                    {
                        HoverButton(j);
                        return;
                    }
                }
            }
            
            HoverButton(i - columns);
        }

        // Given the fact that the buttons are ordered 
        // from left to right, top to bottom
        else if (IsKeyPressed(KEY_RIGHT))
        {
            if (hoveredButton->GetRect().x >= rightMargin && 
                i + 1 >= buttons.size())
            {
                HoverButton(0);
                return;
            }

            HoverButton(i + 1);
        }
        else if (IsKeyPressed(KEY_LEFT))
        {
            if (hoveredButton->GetRect().x <= leftMargin && 
                i == 0)
            {
                HoverButton(buttons.size() - 1);
                return;
            }
            HoverButton(i - 1);
        }
    }
}

void ButtonGroup::HoverButton(int index)
{
    buttons[index]->SetButtonState(HOVER);
    hoveredButton = buttons[index];
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