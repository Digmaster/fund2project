#include "Components/Render/BraveAdventurerAnimatedComponent.h"

#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

BraveAdventurerAnimatedComponent::BraveAdventurerAnimatedComponent()
{
    currDir = 1;
}

void BraveAdventurerAnimatedComponent::go(sf::Time fps) {
    AnimatedComponent::go(fps);
    MovementComponent* movement = ComponentManager::getInst().moveSym.getComponent(getID());
    PhysicsComponent* phys = ComponentManager::getInst().physSym.getComponent(getID());
    if(movement!=NULL) {
        if(movement->getCurrentMovement()=="WalkLeft") {
            if(phys->onGround())
                sprite.setAnimation("WalkLeft");
            else
                sprite.setAnimation("FallLeft");
            currDir = 1;
        }
        if(movement->getCurrentMovement()=="WalkRight") {
            if(phys->onGround())
                sprite.setAnimation("WalkRight");
            else
                sprite.setAnimation("FallRight");
            currDir = 0;
        }
        //cout<<movement->getCurrentMovement()<<endl;
        if(movement->getCurrentMovement() == "still"){
            if(currDir){
                if(phys->onGround())
                    sprite.setAnimation("StandLeft");
                else
                    sprite.setAnimation("FallLeft");
               // cout<<"Standing Right"<<endl;
            }
            else{
                if(phys->onGround())
                    sprite.setAnimation("StandRight");
                else
                    sprite.setAnimation("FallLeft");
               // cout<<"standing Left"<<endl;
            }
        }
        sprite.play();
    }
}
