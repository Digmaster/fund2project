#ifndef STATICSPRITECOMPONENT_H
#define STATICSPRITECOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "SFML/Graphics.hpp"

class StaticSpriteComponent : public RenderComponent
{
    public:
        StaticSpriteComponent() : RenderComponent() {}
        StaticSpriteComponent(sf::Sprite input, unsigned int ID = 0) : RenderComponent(ID) {sprite = input;}
        virtual ~StaticSpriteComponent();
        virtual void go(sf::Time);
    protected:
    private:
        sf::Sprite sprite;
};

#endif // STATICSPRITECOMPONENT_H
