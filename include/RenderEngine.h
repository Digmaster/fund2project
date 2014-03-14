#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "AnimatedSprite.h"
#include "Options.h"
#include <SFML/Graphics.hpp>
#include <deque>
class AnimatedSprite;

class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();
        void render(sf::Time frameTime);
        void addSprite(AnimatedSprite* input);
        void removeSprite(AnimatedSprite* input);
        void flush() {renderList.clear();}
        sf::RenderWindow window;
        sf::View view;
    protected:
    private:
        deque<AnimatedSprite*> renderList;
};

#endif // RENDERENGINE_H
