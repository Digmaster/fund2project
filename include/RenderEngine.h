#pragma once

#include "AnimatedSprite.h"
#include "Options.h"
#include "RenderList.h"
#include <SFML/Graphics.hpp>
#include <deque>

class RenderList;
class AnimatedSprite;

class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();
        void render();
        sf::RenderWindow window;
        void addSprite(AnimatedSprite* input);
        void removeSprite(AnimatedSprite* input);
        void flush() {renderList.clear();}
    protected:
    private:
        deque<AnimatedSprite*> renderList;
};
