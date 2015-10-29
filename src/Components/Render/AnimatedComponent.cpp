#include "Components/Render/AnimatedComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include "Components/Positional/WorldPositionComponent.h"


AnimatedComponent::~AnimatedComponent()
{
    //dtor
}

void AnimatedComponent::go(sf::Time fps, Entity* entity) {
    sprite.update(fps);
    auto posCom = entity->position;
    if(posCom!=NULL) {
        sf::Vector2f position = posCom->getPosition();
        sprite.setPosition(position);
        if(rendEng==NULL) {
            throw std::logic_error("Render engine not initialized yet");
        }
        else {
            rendEng->addSprite(&sprite, posCom->getLayer());
        }
    }
    else { //No world position? // TODO (Thomas Luppi#1#03/16/14): Add checks for screen position, which requires changing the rendering code a bit
    }

    //Add code here to see if the animation has to change!!!
}

sf::Drawable* AnimatedComponent::getDrawable() {
    return &sprite;
}

void AnimatedComponent::setSprite(AnimatedSprite input) {
    sprite = AnimatedSprite(input);
}
