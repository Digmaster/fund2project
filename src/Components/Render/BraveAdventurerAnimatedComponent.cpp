#include "Components/Render/BraveAdventurerAnimatedComponent.h"

#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include "Components/Input/InputComponent.h"
#include "Components/Stats/StatsComponent.h"

BraveAdventurerAnimatedComponent::BraveAdventurerAnimatedComponent() : AnimatedComponent()
{
    currDir = 1;
}

void BraveAdventurerAnimatedComponent::go(sf::Time fps, Entity* entity) {
    AnimatedComponent::go(fps, entity);
    MovementComponent* movement = entity->movement;
    InputComponent* input = entity->input;
    StatsComponent* statsComp = entity->stats;
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
