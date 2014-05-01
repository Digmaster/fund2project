#include "Components/Render/BraveAdventurerAnimatedComponent.h"

#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

BraveAdventurerAnimatedComponent::BraveAdventurerAnimatedComponent() : BraveAdventurerAnimatedComponent(0)
{
    currDir = 1;

}

BraveAdventurerAnimatedComponent::BraveAdventurerAnimatedComponent(unsigned int id) : AnimatedComponent(ID) {
    setID(id);
}

void BraveAdventurerAnimatedComponent::go(sf::Time fps) {
    AnimatedComponent::go(fps);
    MovementComponent* movement = ComponentManager::getInst().moveSym.getComponent(getID());
    InputComponent* input = ComponentManager::getInst().inputSym.getComponent(getID());
    StatsComponent* statsComp = ComponentManager::getInst().statSym.getComponent(getID());
    if(movement!=NULL && input!=NULL) {
        if(movement->getState()==MoveState::onGround) {
            if(input->fireDir < 90 && input->fireDir > -90)
                sprite.setAnimation("StandRight");
            else
                sprite.setAnimation("StandLeft");
        }
        if(movement->getState()==MoveState::leftWalk) {
            sprite.setAnimation("WalkLeft");
        }
        if(movement->getState()==MoveState::rightWalk) {
            sprite.setAnimation("WalkRight");
        }
        if(movement->getState()==MoveState::inAir) {
            if(input->fireDir < 90 && input->fireDir > -90)
                sprite.setAnimation("FallRight");
            else
                sprite.setAnimation("FallLeft");
        }

        if(movement->getState()==MoveState::onLadder)
            sprite.setAnimation("ClimbStill");
        if(movement->getState()==MoveState::ladderRight)
            sprite.setAnimation("ClimbRight");
        if(movement->getState()==MoveState::ladderLeft)
            sprite.setAnimation("ClimbLeft");
        if(movement->getState()==MoveState::ladderUp)
            sprite.setAnimation("ClimbUp");
        if(movement->getState()==MoveState::ladderDown)
            sprite.setAnimation("ClimbDown");
        if(movement->getState()==MoveState::jumping) {
            if(input->walkLeft)
                sprite.setAnimation("JumpLeft");
            else
                sprite.setAnimation("JumpRight");
        }
        sprite.play();
    }
    if(statsComp){
        if(statsComp->isDead()==true){
            sprite.setAnimation("Death");\
        }
    }
}
