#pragma once
#include "raylib.h"
#include "src/utils/Utils.hpp"

class Renderable
{
    public:
        Renderable();
        
        virtual void Draw();
        Vector2 GetPosition() { return position; }
        
    protected:
        Texture2D image;
        Vector2 position;
};