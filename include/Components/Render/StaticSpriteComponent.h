#ifndef STATICSPRITECOMPONENT_H
#define STATICSPRITECOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "SFML/Graphics.hpp"
#include <string>

///Creates a simple, one image, non-moving image
class StaticSpriteComponent : public RenderComponent
{
    public:
        StaticSpriteComponent() : RenderComponent() {}
        StaticSpriteComponent(sf::Sprite input, unsigned int ID = 0) : RenderComponent(ID) {sprite = input;}
        StaticSpriteComponent(std::string texture, const sf::IntRect &rectangle, unsigned int ID = 0);
        virtual ~StaticSpriteComponent();
        virtual void go(sf::Time);
        sf::Drawable* getDrawable();
    protected:
    private:
        sf::Sprite sprite;
};

#endif // STATICSPRITECOMPONENT_H
