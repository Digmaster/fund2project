#include "AnimatedComponent.h"
#include "ComponentManager.h"

AnimatedComponent::AnimatedComponent()
{
    //ctor
}

AnimatedComponent::~AnimatedComponent()
{
    //dtor
}

void AnimatedComponent::go(sf::Time fps) {
    sprite.update(fps);
    sf::Vector2f position = ComponentManager::getInst().posSym.getComponent(getID())->getPosition();
    sprite.setPosition(position);
    //Add code here to see if the animation has to change!!!
}
