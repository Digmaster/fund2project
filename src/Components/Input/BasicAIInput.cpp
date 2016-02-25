#include "BasicAIInput.h"

#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include <cmath>

BasicAIInput::BasicAIInput() : InputComponent()
{
    gotoLeft = false;
    walkTimer = sf::Time::Zero;
}

BasicAIInput::~BasicAIInput()
{
    //dtor
}

void BasicAIInput::go(sf::Time frameTime, Entity* entity)
{
    walkTimer-=frameTime;
    static const sf::Time maxWalkTime = sf::seconds(5); //5 seconds of walk in either direction

    std::shared_ptr<WorldPositionComponent> position = entity->getPosition();
    unsigned int mainCharID = compMan->name2ID("MainChar");

    std::shared_ptr<WorldPositionComponent> enePosComp = entity->getPosition();
    std::shared_ptr<WorldPositionComponent> advPosComp = (*compMan)[mainCharID]->getPosition();
    std::shared_ptr<PhysicsComponent> physics = entity->getPhysics();

    if(!enePosComp || !advPosComp)
    {
        return;
    }

    sf::Vector2f enePos = enePosComp->getPosition();
    sf::Vector2f advPos = advPosComp->getPosition();

    int distance = (advPos.x - enePos.x)*(advPos.x - enePos.x)+(advPos.y - enePos.y)*(advPos.y - enePos.y);
    int maxAttackDistance = 200;

    fireDir = atan2(advPos.y-enePos.y,advPos.x-enePos.x) * -180.0f/3.14159265f;
    fire = false;

    if(distance <= maxAttackDistance * maxAttackDistance)
    {
        run = true;
        fire = true;
        if (advPos.x > enePos.x)
        {
            walkRight = true;
            walkLeft = false;
        }
        else if (advPos.x < enePos.x)
        {
            walkRight = false;
            walkLeft = true;
        }
        if (advPos.y+10 < enePos.y)
        {
            if(physics!=nullptr && physics->overLadder() && !physics->onTop())
            {
                walkRight = false;
                walkLeft = false;
            }
            jump = true;
            climbUp = true;
            climbDown = false;
        }
        else if (advPos.y-10 > enePos.y)
        {
            if(physics!=nullptr && physics->overLadder() && !physics->onGround())
            {
                walkRight = false;
                walkLeft = false;
            }
            jump = false;
            climbUp = false;
            climbDown = true;
        }
    }
    else
    {
        //if we have walked long enough OR there's something in our way AND we're on the ground
        if(walkTimer <= sf::Time::Zero || (physics->onGround() && ((physics->onRight() && !gotoLeft) || (physics->onLeft() && gotoLeft))))
        {
            walkTimer = maxWalkTime;
            gotoLeft = !gotoLeft;
        }

        if(!gotoLeft)
        {
            run = false;
            walkRight = true;
            walkLeft = false;
        }
        else
        {
            run = false;
            walkRight = false;
            walkLeft = true;
        }
    }
}
