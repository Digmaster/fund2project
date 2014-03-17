#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "Components/Render/RenderComponent.h"
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
        void addSprite(sf::Drawable* input);
        void addScreenSprite(sf::Drawable* input);
        void removeSprite(sf::Drawable* input);
        void removeScreenSprite(sf::Drawable* input);
        void flush() {renderList.clear();}
        sf::RenderWindow window;
        sf::View view;
    protected:
    private:
        std::deque<sf::Drawable*> renderList;
        std::deque<sf::Drawable*> screenRenderList;
};

#endif // RENDERENGINE_H
