#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>
#include <Box2D/Box2D.h>

class TextComponent : public RenderComponent
{
    public:
        TextComponent(std::string text, int fontSize = 30, sf::Color color = sf::Color::Black,int fontStyle = 0, sf::Font* = nullptr);
        TextComponent(uint32 thing, int fontSize = 30, sf::Color color = sf::Color::Black,int fontStyle = 0, sf::Font* = nullptr);
        virtual ~TextComponent();

        virtual void go(sf::Time, Entity* entity);
        sf::Drawable* getDrawable() {return &textDrawable;}

        Entity::listener& getHandler();
        void HandleMessage(Events event, EventObj* message, Entity* entity);

    protected:
    private:
        sf::Text textDrawable;
        uint32 thingToWatch;
};

enum ThingsToWatch
{
    nothing,
    health
};

#endif // TEXTCOMPONENT_H
