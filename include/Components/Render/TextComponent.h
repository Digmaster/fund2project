#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "SFML/Graphics.hpp"
#include <string>

class TextComponent : public RenderComponent
{
    public:
        TextComponent(std::string text, int fontSize = 30, sf::Color color = sf::Color::Black,int fontStyle = 0, sf::Font* = nullptr);
        virtual ~TextComponent();

        virtual void go(sf::Time, Entity* entity);
        sf::Drawable* getDrawable() {return &textDrawable;}
    protected:
    private:
        sf::Text textDrawable;
};

#endif // TEXTCOMPONENT_H
