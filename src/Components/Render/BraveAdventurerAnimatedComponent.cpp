#include "Components/Render/BraveAdventurerAnimatedComponent.h"

#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include "Components/Input/InputComponent.h"
#include "Components/Stats/StatsComponent.h"

BraveAdventurerAnimatedComponent::BraveAdventurerAnimatedComponent() : AnimatedComponent()
{
    currDir = 1;
    cooldownValues.resize(getNumCooldowns(), false);
}

ComponentBase::listenerList BraveAdventurerAnimatedComponent::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&BraveAdventurerAnimatedComponent::HandleMovementChange, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(typeid(MovementComponent), handler));
    out.push_back(listenerPair(typeid(StatsComponent), handler));
    return out;
}

void BraveAdventurerAnimatedComponent::go(sf::Time fps, Entity* entity) {
    for(auto it = cooldowns.begin(); it != cooldowns.end();)
    {
        // Subtract the current time
        it->second -= fps;

        //Delete any old cooldowns
        if(it->second <= sf::Time::Zero)
        {
            cooldownValues[it->first] = false;
            it = cooldowns.erase(it);
        }
        else
        {
            cooldownValues[it->first] = true;
            it++;
        }
    }

    if(cooldownValues[HURT])
        sprite.setColor(sf::Color::Red);
    else
        sprite.setColor(sf::Color::White);

    AnimatedComponent::go(fps, entity);
    std::shared_ptr<MovementComponent> movement = entity->getMovement();
    std::shared_ptr<InputComponent> input = entity->getInput();
    std::shared_ptr<StatsComponent> statsComp = entity->getStats();
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
            sprite.setAnimation("Dissipate");
        }
    }
}

void BraveAdventurerAnimatedComponent::HandleMovementChange(Events event, EventObj* message, Entity* entity)
{
    switch(event)
    {
    case Events::HEALTH_CHANGE:
        cooldowns[HURT] = getHealthCooldown();
        break;
    }
}
