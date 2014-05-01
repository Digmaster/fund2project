#include "Components/Movement/EnemyMovement.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Input/InputComponent.h"

using namespace std;

EnemyMovement::EnemyMovement() :EnemyMovement(0)
{

}

EnemyMovement::EnemyMovement(unsigned int ID) : MovementComponent(ID) {
    currState = rightWalk;
    nextState = rightWalk;
}

void EnemyMovement::go(sf::Time frameTime) {
    walkTimer+=frameTime;
    PhysicsComponent* physics = ComponentManager::getInst().physSym.getComponent(getID());
    unsigned int mainCharID = compMan->name2ID("MainChar");
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    InputComponent* input = compMan->inputSym.getComponent(getID());
    StatsComponent* stats = compMan->statSym.getComponent(mainCharID);
    int walkSpeed = 5;
    int attackSpeed = 5;
    int maxAirSpeed = 2;
    //int maxLadderSpeed = 5;
    int maxJumpSpeed = 10;
    //int climbSpeed = 5;
    sf::Time maxJumpTime = sf::milliseconds(25); //.25 seconds of jump
    sf::Time maxWalkTime = sf::seconds(5); //5 seconds of walk in either direction
    WorldPositionComponent* enePosComp = compMan->posSym.getComponent(getID());
    WorldPositionComponent* advPosComp = compMan->posSym.getComponent(mainCharID);
    if(physics && enePosComp && advPosComp) { //Find in physics states
        sf::Vector2f enePos = enePosComp->getPosition();
        sf::Vector2f advPos = advPosComp->getPosition();
        b2Body* body = physics->getBody();
        b2Vec2 velocity = body->GetLinearVelocity();
        //physics->on
        //body->SetLinearVelocity(b2Vec2(uuuhi,body->GetLinearVelocity().y))

        changed = false;

        if(nextState!=currState) { //State changers
            if(nextState==MoveState::jumping)
                jumpTimer = sf::milliseconds(0);
            if(nextState==(MoveState::rightWalk || MoveState::leftWalk))
                walkTimer = sf::seconds(0);

            currState=nextState; //Set currState to nextState
            changed = true;
        }
        int distance = abs(advPos.x - enePos.x);
        int maxAttackDistance = 64;
        if(stats) {
            if((physics->onRight() && (physics->touchingRight() == mainCharID)) || (physics->onLeft() && (physics->touchingLeft() == mainCharID)))
                stats->setHealth(0);
        }

        switch(currState) {
        case MoveState::rightWalk:
            body->SetLinearVelocity(b2Vec2(walkSpeed,body->GetLinearVelocity().y));
            if(distance <= maxAttackDistance)
                nextState = MoveState::attack;
            else if ((walkTimer >= maxWalkTime) || (physics->onRight()))
                nextState = MoveState::leftWalk;
            if(!physics->onGround())
                nextState = MoveState::inAir;
            break;
        case MoveState::leftWalk:
            body->SetLinearVelocity(b2Vec2(-walkSpeed,body->GetLinearVelocity().y));
            if(distance <= maxAttackDistance)
                nextState = MoveState::attack;
            else if ((walkTimer >= maxWalkTime) || (physics->onLeft()))
                nextState = MoveState::rightWalk;
            if(!physics->onGround())
                nextState = MoveState::inAir;
            break;
        case MoveState::attack:
            if (advPos.x > enePos.x)
                body->SetLinearVelocity(b2Vec2(attackSpeed,body->GetLinearVelocity().y));
            else if (advPos.x < enePos.x)
                body->SetLinearVelocity(b2Vec2(-attackSpeed,body->GetLinearVelocity().y));
            if ((distance > maxAttackDistance) && (advPos.x > enePos.x))
                nextState = MoveState::rightWalk;
            else if ((distance > maxAttackDistance) && (advPos.x < enePos.x))
                nextState = MoveState::leftWalk;
            if (advPos.y < enePos.y)
                nextState = MoveState::jumping;
            if(!physics->onGround())
                nextState = MoveState::inAir;
            break;
        case MoveState::inAir:
            if(physics->onGround()) //Landed
                nextState = MoveState::leftWalk;
            /*if(input->walkLeft && velocity.x > -maxAirSpeed) //Move left
                body->ApplyForceToCenter(b2Vec2(-50.0f-velocity.x*50.0f/maxAirSpeed,0),true);
            if(input->walkRight && velocity.x < maxAirSpeed) //Move right
                body->ApplyForceToCenter(b2Vec2(50.0f-velocity.x*50.0f/maxAirSpeed,0),true);
            if((input->climbUp || input->climbDown) && physics->overLadder()) //Start climbing on a ladder
                nextState = MoveState::onLadder;*/
            break;
        /*case MoveState::onGround:
            if(input->walkLeft && velocity.x > -maxGroundSpeed) //Move left
                body->ApplyForceToCenter(b2Vec2(-100.0f-velocity.x*100.0f/maxGroundSpeed,0),true);
            if(input->walkRight && velocity.x < maxGroundSpeed) //Move right
                body->ApplyForceToCenter(b2Vec2(100.0f-velocity.x*100.0f/maxGroundSpeed,0),true);
            if((!input->walkLeft && !input->walkRight) || (input->walkLeft && input->walkRight)) //No movement, slow him
                body->ApplyForceToCenter(b2Vec2(-25*velocity.x,0),true);
            if(!physics->onGround()) //in air!
                nextState = MoveState::inAir;
            if(input->jump) //Jump
                nextState = MoveState::jumping;
            if((input->climbUp || input->climbDown) && physics->overLadder()) //Start climbing on a ladder
                nextState = MoveState::onLadder;
            break;*/
        case MoveState::jumping:
            jumpTimer += frameTime;
            if(jumpTimer <= maxJumpTime)
                body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x,maxJumpSpeed));
            else
                nextState = MoveState::inAir;
            break;
        /*case MoveState::onLadder:
            if(input->climbUp) //climb up
                body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, climbSpeed));
            if(input->climbDown) //climb down
                body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -climbSpeed));
            if(input->jump) //jump off
                nextState = MoveState::jumping;
            if(!physics->overLadder()) //off Ladder
                nextState = MoveState::inAir;
            if(velocity.x > -maxLadderSpeed && velocity.x < maxLadderSpeed) { //Movement
                if(input->walkLeft)
                    body->ApplyForceToCenter(b2Vec2(-100.0f-velocity.x*100.0f/maxLadderSpeed,0),true);
                if(input->walkRight)
                    body->ApplyForceToCenter(b2Vec2(100.0f-velocity.x*100.0f/maxLadderSpeed,0),true);
            }
            break;*/
        }
    }
}
