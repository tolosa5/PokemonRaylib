#pragma once
#include "raylib.h"

class Utils
{
    public:
        static Color YellowColor () { return {243, 216, 63, 255}; }
        static Color GreyBgColor() { return {30, 30, 30, 255}; }

        static int PixelSize() { return 3; }
        static int GetOffset() { return 50; }

        static bool IsOutOfScreenSidewards(
            Vector2 position, int width = 0)
        {
            return position.x > (
                GetScreenWidth() - Utils::GetOffset() / 2) - width || 
                position.x < Utils::GetOffset() / 2;
        }

        static bool IsOutOfScreenUpwards(
            Vector2 position, int height)
        {
            return position.y > 
            GetScreenHeight() - (Utils::GetOffset() * 2) || 
                position.y < Utils::GetOffset() / 2 - height;
        }
};