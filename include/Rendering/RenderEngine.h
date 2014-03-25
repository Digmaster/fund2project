#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "Components/Render/RenderComponent.h"
#include "Options.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include <map>
class AnimatedSprite;
class PhysicsEngine;

class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();
        void render(sf::Time frameTime, PhysicsEngine*);
        void addSprite(sf::Drawable* input, int layer = 0);
        void addScreenSprite(sf::Drawable* input);
        void removeSprite(sf::Drawable* input, int layer);
        void removeScreenSprite(sf::Drawable* input);
        void flush() {renderList.clear();}
        void setBackgroundColor(sf::Color input) {bkColor = input;}
        void toggleDebug();
        sf::RenderWindow window;
        sf::View view;
    protected:
    private:
        bool debugEnabled;
        sf::Color bkColor;

        std::map<int, std::deque<sf::Drawable*> > renderList;
        std::deque<sf::Drawable*> screenRenderList;
};

#endif // RENDERENGINE_H
