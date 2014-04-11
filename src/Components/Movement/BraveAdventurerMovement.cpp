#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Input/InputComponent.h"

using namespace std;

BraveAdventurerMovement::BraveAdventurerMovement() :BraveAdventurerMovement(0)
{

}

BraveAdventurerMovement::BraveAdventurerMovement(unsigned int ID) : MovementComponent(ID) {

}

void BraveAdventurerMovement::go(sf::Time frameTime) {
    PhysicsComponent* physics = ComponentManager::getInst().physSym.getComponent(getID());
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    InputComponent* input = compMan->inputSym.getComponent(getID());
    int maxGroundSpeed = 20;
    int maxAirSpeed = 15;
    int maxLadderSpeed = 5;
    int maxJumpSpeed = 10;
    int climbSpeed = 5;
    sf::Time maxJumpTime = sf::milliseconds(25); //.25 seconds of jump
    if(physics!=NULL) { //Find in physics states
        b2Body* body = physics->getBody();
        b2Vec2 velocity = body->GetLinearVelocity();

        if(nextState!=currState) { //State changers
            if((nextState>=MoveState::onLadder && nextState<=MoveState::ladderDown) && !(currState>=MoveState::onLadder && currState<=MoveState::ladderDown)) { //Remove gravity and whatnot
                physics->getBody()->SetGravityScale(0);
                physics->getBody()->SetLinearDamping(8.0f);
            }
            if(currState>=MoveState::onLadder && currState<=MoveState::ladderDown && !(nextState>=MoveState::onLadder && nextState<=MoveState::ladderDown)) {
                physics->getBody()->SetGravityScale(1);
                physics->getBody()->SetLinearDamping(0.0f);
            }
            if(nextState==MoveState::jumping)
                jumpTimer = sf::milliseconds(0);

            currState=nextState; //Set currState to nextState
        }

        switch(currState) {
        case MoveState::inAir:
            if(physics->onGround()) //Landed
                nextState = MoveState::onGround;
            if(input->walkLeft && velocity.x > -maxAirSpeed) //Move left
                body->ApplyForceToCenter(b2Vec2(-50.0f-velocity.x*50.0f/maxAirSpeed,0),true);
            if(input->walkRight && velocity.x < maxAirSpeed) //Move right
                body->ApplyForceToCenter(b2Vec2(50.0f-velocity.x*50.0f/maxAirSpeed,0),true);
            if((input->climbUp || input->climbDown) && physics->overLadder()) //Start climbing on a ladder
                nextState = MoveState::onLadder;
            break;
        case MoveState::onGround:
            body->ApplyForceToCenter(b2Vec2(-25*velocity.x,0),true); //Slow x movement
            if(input->walkLeft) //Move left
                nextState=MoveState::leftWalk;
            if(input->walkRight) //Move right
                nextState=MoveState::rightWalk;
            if(!physics->onGround()) //in air!
                nextState = MoveState::inAir;
            if(input->jump) //Jump
                nextState = MoveState::jumping;
            if((input->climbUp || input->climbDown) && physics->overLadder()) //Start climbing on a ladder
                nextState = MoveState::onLadder;
            break;
        case MoveState::leftWalk:
            if(input->walkLeft && velocity.x > -maxGroundSpeed) //Contimue to walk left
                body->ApplyForceToCenter(b2Vec2(-100.0f-velocity.x*100.0f/maxGroundSpeed,0),true);
            if(!input->walkLeft)
                nextState= MoveState::onGround;
            if(!physics->onGround()) //in air!
                nextState = MoveState::inAir;
            if(input->jump) //Jump
                nextState = MoveState::jumping;
            if((input->climbUp || input->climbDown) && physics->overLadder()) //Start climbing on a ladder
                nextState = MoveState::onLadder;
            break;
        case MoveState::rightWalk:
            if(input->walkRight && velocity.x < maxGroundSpeed) //Contimue to walk left
                body->ApplyForceToCenter(b2Vec2(100.0f-velocity.x*100.0f/maxGroundSpeed,0),true);
            if(!input->walkRight)
                nextState= MoveState::onGround;
            if(!physics->onGround()) //in air!
                nextState = MoveState::inAir;
            if(input->jump) //Jump
                nextState = MoveState::jumping;
            if((input->climbUp || input->climbDown) && physics->overLadder()) //Start climbing on a ladder
                nextState = MoveState::onLadder;
            break;
        case MoveState::jumping:
            jumpTimer += frameTime;
            if(jumpTimer <= maxJumpTime && input->jump)
                body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x,maxJumpSpeed));
            else
                nextState = MoveState::inAir;
            break;
        case MoveState::onLadder:
            if(input->climbUp) //climb up
                nextState=MoveState::ladderUp;
            if(input->climbDown) //climb down
                nextState=MoveState::ladderDown;
            if(input->jump) //jump off
                nextState = MoveState::jumping;
            if(!physics->overLadder()) //off Ladder
                nextState = MoveState::inAir;
            if(velocity.x > -maxLadderSpeed && velocity.x < maxLadderSpeed) { //Movement
                if(input->walkLeft)
                    nextState=MoveState::ladderLeft;
                if(input->walkRight)
                    nextState=MoveState::ladderRight;
            }
            break;
        case MoveState::ladderLeft:
            if(input->walkLeft && velocity.x >= -maxLadderSpeed) //Moving
                body->ApplyForceToCenter(b2Vec2(-100.0f-velocity.x*100.0f/maxLadderSpeed,0),true);
            else
                nextState=MoveState::onLadder;
            if(!physics->overLadder()) //No longer on ladder
                nextState=MoveState::inAir;
            if(input->jump) //jump off
                nextState = MoveState::jumping;
            break;
        case MoveState::ladderRight:
            if(input->walkRight && velocity.x <= maxLadderSpeed) //Moving
                body->ApplyForceToCenter(b2Vec2(100.0f-velocity.x*100.0f/maxLadderSpeed,0),true);
            else
                nextState=MoveState::onLadder;
            if(!physics->overLadder()) //No longer on ladder
                nextState=MoveState::inAir;
            if(input->jump) //jump off
                nextState = MoveState::jumping;
            break;
        case MoveState::ladderUp:
            if(input->climbUp && velocity.y <= maxLadderSpeed) //Moving
                body->ApplyForceToCenter(b2Vec2(0,100.0f-velocity.x*100.0f/maxLadderSpeed),true);
            else
                nextState=MoveState::onLadder;
            if(!physics->overLadder()) //No longer on ladder
                nextState=MoveState::inAir;
            if(input->jump) //jump off
                nextState = MoveState::jumping;
            break;
        case MoveState::ladderDown:
            if(input->climbDown && velocity.y >= -maxLadderSpeed) //Moving
                body->ApplyForceToCenter(b2Vec2(0,-100.0f-velocity.x*100.0f/maxLadderSpeed),true);
            else
                nextState=MoveState::onLadder;
            if(!physics->overLadder()) //No longer on ladder
                nextState=MoveState::inAir;
            if(input->jump) //jump off
                nextState = MoveState::jumping;
            break;
        }
    }
}
