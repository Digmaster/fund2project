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
        void render();
        void addSprite(sf::Drawable* input);
        void removeSprite(sf::Drawable* input);
        void flush() {renderList.clear();}
        sf::RenderWindow window;
        sf::View view;
    protected:
    private:
        deque<sf::Drawable*> renderList;
};

#endif // RENDERENGINE_H
