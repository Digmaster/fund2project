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
    if(movement!=NULL) {
        if(movement->getCurrentMovement() == "WalkLeft") {
            sprite.setAnimation("WalkLeft");
            currDir = 1;
        }
        if(movement->getCurrentMovement() == "WalkRight") {
            sprite.setAnimation("WalkRight");
            currDir = 0;
        }
        //cout<<movement->getCurrentMovement()<<endl;
        if(movement->getCurrentMovement() == "none"){
            if(currDir){
                sprite.setAnimation("StandLeft");
               // cout<<"Standing Right"<<endl;
            }
            else{
                sprite.setAnimation("StandRight");
               // cout<<"standing Left"<<endl;
            }
        }
        sprite.play();
    }
}
