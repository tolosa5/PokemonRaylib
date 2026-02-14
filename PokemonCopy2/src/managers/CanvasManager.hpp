#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#pragma once

#include <iostream>
#include "raylib.h"

class Game;

class CanvasManager
{
public:

    CanvasManager();
    ~CanvasManager();

    void Update(Game* game);

private:
    
};

#endif