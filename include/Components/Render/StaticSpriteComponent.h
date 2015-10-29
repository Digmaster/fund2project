#ifndef STATICSPRITECOMPONENT_H
#define STATICSPRITECOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "SFML/Graphics.hpp"
#include <string>

///Creates a simple, one image, non-moving image
class StaticSpriteComponent : public RenderComponent
{
    public:
        StaticSpriteComponent(sf::Sprite input) : RenderComponent() {sprite = input;}
        StaticSpriteComponent(std::string texture, const sf::IntRect &rectangle);
        virtual ~StaticSpriteComponent();
        virtual void go(sf::Time, Entity* entity);
        sf::Drawable* getDrawable();
    protected:
    private:
        sf::Sprite sprite;
};

#endif // STATICSPRITECOMPONENT_H
