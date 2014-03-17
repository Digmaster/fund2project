#include "Components/Render/BraveAdventurerAnimatedComponent.h"

#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

BraveAdventurerAnimatedComponent::BraveAdventurerAnimatedComponent()
{
    //ctor
}

void BraveAdventurerAnimatedComponent::go(sf::Time fps) {
    AnimatedComponent::go(fps);
    MovementComponent* movement = ComponentManager::getInst().moveSym.getComponent(getID());
    if(movement!=NULL) {
        if(movement->getCurrentMovement() == "WalkUp")
            sprite.setAnimation("WalkUp");
        if(movement->getCurrentMovement() == "WalkDown")
            sprite.setAnimation("WalkDown");
        if(movement->getCurrentMovement() == "WalkLeft")
            sprite.setAnimation("WalkLeft");
        if(movement->getCurrentMovement() == "WalkRight")
            sprite.setAnimation("WalkRight");
        sprite.play();
        if(movement->getCurrentMovement() == "none")
            sprite.stop();
    }
}
