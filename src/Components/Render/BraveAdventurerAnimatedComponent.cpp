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
    InputComponent* input = ComponentManager::getInst().inputSym.getComponent(getID());
    if(movement!=NULL && input!=NULL) {
        if(movement->getState()==MoveState::onGround) {
            if(input->walkLeft && !input->walkRight)
                sprite.setAnimation("WalkLeft");
            else if(input->walkRight && !input->walkLeft)
                sprite.setAnimation("WalkRight");
            else {
                if(input->fireDir < 90 && input->fireDir > -90)
                    sprite.setAnimation("StandRight");
                else
                    sprite.setAnimation("StandLeft");
            }
        }
        if(movement->getState()==MoveState::inAir) {
            if(input->walkLeft && !input->walkRight)
                sprite.setAnimation("JumpLeft");
            else if(input->walkRight && !input->walkLeft)
                sprite.setAnimation("JumpRight");
            else {
                if(input->fireDir < 90 && input->fireDir > -90)
                    sprite.setAnimation("FallRight");
                else
                    sprite.setAnimation("FallLeft");
            }
        }
        if(movement->getState()==MoveState::onLadder) {
            if(input->climbUp)
                sprite.setAnimation("ClimbUp");
            if(input->climbDown)
                sprite.setAnimation("ClimbDown");
            else if(input->walkLeft)
                sprite.setAnimation("ClimbLeft");
            else if(input->walkRight)
                sprite.setAnimation("ClimbRight");
            else {
                sprite.setAnimation("ClimbStill");
            }
        }
        if(movement->getState()==MoveState::jumping) {
            if(input->walkLeft)
                sprite.setAnimation("JumpLeft");
            else
                sprite.setAnimation("JumpRight");
        }
        sprite.play();
    }
}
