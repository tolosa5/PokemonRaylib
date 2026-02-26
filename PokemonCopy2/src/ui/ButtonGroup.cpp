#include "ButtonGroup.hpp"

ButtonGroup::ButtonGroup(std::vector<Button*>& buttons, 
    GroupMode mode, int rows, int columns) 
    : rows(rows), columns(columns), buttons(buttons)
{
    this->mode = mode;
    if (!buttons.empty())
        HoverButton(0);
    GridSetup();
}

void ButtonGroup::Update()
{
    if (InputManager::GetCurrentMode() != UI)
        return;
    
    ButtonsIteration();
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
    if (buttons.empty())
        return;

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (!buttons[i])
            continue;

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
            GridIteration();
            break;
        }
    }
}

void ButtonGroup::VerticalIteration()
{
    if (buttons.empty())
        return;

    if (IsKeyPressed(KEY_DOWN))
    {
        Button* hoveredButton = GetHoveredButton();

        if (!hoveredButton)
        {
            HoverButton(0);
            return;
        }
                
        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i] == hoveredButton)
            {
                hoveredButton->SetButtonState(IDLE);
                const size_t nextIndex = (i + 1) % buttons.size();
                HoverButton(static_cast<int>(nextIndex));
                break;
            }
        }
    }

    if (IsKeyPressed(KEY_UP))
    {
        Button* hoveredButton = GetHoveredButton();

        if (!hoveredButton)
        {
            HoverButton(0);
            return;
        }
        
        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i] == hoveredButton)
            {
                hoveredButton->SetButtonState(IDLE);
                const size_t prevIndex = (i == 0) ? (buttons.size() - 1) : (i - 1);
                HoverButton(static_cast<int>(prevIndex));
                break;
            }
        }
    }
}

void ButtonGroup::HorizontalIteration()
{
    if (buttons.empty())
        return;

    if (IsKeyPressed(KEY_RIGHT))
    {
        Button* hoveredButton = GetHoveredButton();
        if (!hoveredButton)
        {
            HoverButton(0);
            return;
        }
                
        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i] == hoveredButton)
            {
                hoveredButton->SetButtonState(IDLE);
                const size_t nextIndex = (i + 1) % buttons.size();
                HoverButton(static_cast<int>(nextIndex));
                break;
            }
        }
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        Button* hoveredButton = GetHoveredButton();
        if (!hoveredButton)
        {
            HoverButton(0);
            return;
        }

        for (size_t i = 0; i < buttons.size(); ++i)
        {
            if (buttons[i] == hoveredButton)
            {
                hoveredButton->SetButtonState(IDLE);
                const size_t prevIndex = (i == 0) ? (buttons.size() - 1) : (i - 1);
                HoverButton(static_cast<int>(prevIndex));
                break;
            }
        }
    }
}

void ButtonGroup::GridIteration()
{
    if (buttons.empty())
        return;

    if (!IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) && 
        !IsKeyPressed(KEY_RIGHT) && !IsKeyPressed(KEY_LEFT))
        return;

    Button* hoveredButton = GetHoveredButton();
    if (!hoveredButton)
    {
        HoverButton(0);
        return;
    }
            
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i] != hoveredButton)
            continue;

        hoveredButton->SetButtonState(IDLE);

        if (IsKeyPressed(KEY_DOWN))
        {
            if (hoveredButton->GetRect().y >= bottomMargin)
            {
                for (size_t j = 0; j < buttons.size(); ++j)
                {
                    if (buttons[j]->GetRect().x == hoveredButton->GetRect().x &&
                        buttons[j]->GetRect().y == topMargin)
                    {
                        HoverButton(j);
                        return;
                    }
                }
            }
            
            int target = static_cast<int>(i) + columns;
            if (target >= static_cast<int>(buttons.size()))
                target %= static_cast<int>(buttons.size());
            HoverButton(target);
        }
        else if (IsKeyPressed(KEY_UP))
        {
            if (hoveredButton->GetRect().y <= topMargin)
            {
                for (size_t j = 0; j < buttons.size(); ++j)
                {
                    if (buttons[j]->GetRect().x == hoveredButton->GetRect().x &&
                        buttons[j]->GetRect().y == bottomMargin)
                    {
                        HoverButton(j);
                        return;
                    }
                }
            }
            
            int target = static_cast<int>(i) - columns;
            while (target < 0)
                target += static_cast<int>(buttons.size());
            HoverButton(target);
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
        break;
    }
}

void ButtonGroup::HoverButton(int index)
{
    if (buttons.empty())
        return;

    if (index < 0 || index >= static_cast<int>(buttons.size()))
        return;

    if (!buttons[index])
        return;

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