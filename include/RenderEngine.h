#pragma once

#include "AnimatedSprite.h"
#include "Options.h"
#include "RenderList.h"
#include <SFML/Graphics.hpp>
#include <deque>

class RenderList;

class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();
        RenderList* rendList;
        void render();
        sf::RenderWindow window;
    protected:
    private:
};
