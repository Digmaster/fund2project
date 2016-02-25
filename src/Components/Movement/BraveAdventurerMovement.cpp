#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Input/InputComponent.h"
#include "Components/Entity.h"

#include "Components/Render/StaticSpriteComponent.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Script/KillScript.h"
#include "Components/Stats/StatsComponent.h"
#include "Components/Script/ExplodeScript.h"
#include "Components/Movement/AccelerateMovement.h"

using namespace std;

BraveAdventurerMovement::BraveAdventurerMovement() : MovementComponent() {

}

void BraveAdventurerMovement::go(sf::Time frameTime, Entity* entity) {
    std::shared_ptr<PhysicsComponent> physics = entity->getPhysics();
    std::shared_ptr<InputComponent> input = entity->getInput();
    std::shared_ptr<WorldPositionComponent> position = entity->getPosition();
    std::shared_ptr<StatsComponent> stats = entity->getStats();

    float maxGroundSpeed = 20;
    float maxAirSpeed = 15;
    float maxLadderSpeed = 5;
    float maxJumpSpeed = 20;
    sf::Time maxJumpTime = sf::milliseconds(25); //.25 seconds of jump

    if(stats!=nullptr)
    {
        float speed = stats->getSpeed();
        maxGroundSpeed *= speed;
        maxAirSpeed *= speed;
        maxLadderSpeed *= speed;
        maxJumpSpeed *= speed;
    }

    if(physics!=NULL) { //Find in physics states
        b2Body* body = physics->getBody();
        b2Vec2 velocity = body->GetLinearVelocity();

        if(nextState!=currState) { //State changers
            if((nextState>=MoveState::onLadder && nextState<=MoveState::ladderDown) && !(currState>=MoveState::onLadder && currState<=MoveState::ladderDown)) { //Remove gravity and whatnot
                entity->callListeners(Events::CLIMBING_START);
                physics->getBody()->SetGravityScale(0);
                physics->getBody()->SetLinearDamping(8.0f);
            }
            if(currState>=MoveState::onLadder && currState<=MoveState::ladderDown && !(nextState>=MoveState::onLadder && nextState<=MoveState::ladderDown)) {
                physics->getBody()->SetGravityScale(1);
                physics->getBody()->SetLinearDamping(0.0f);
                entity->callListeners(Events::CLIMBING_END);
            }
            if(nextState==MoveState::jumping)
            {
                jumpTimer = sf::milliseconds(0);
                entity->callListeners(Events::JUMP);
            }

            if(nextState == MoveState::onGround && currState == MoveState::inAir )
            {
                entity->callListeners(Events::FALL_END);
            }

            if(nextState == MoveState::inAir && currState == MoveState::onGround )
            {
                entity->callListeners(Events::FALL_START);
            }

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
            if(input->fire && fireTimer <= sf::seconds(0))
                nextState = MoveState::attack;
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
            if(input->fire && fireTimer <= sf::seconds(0))
                nextState = MoveState::attack;
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
            if(input->fire && fireTimer <= sf::seconds(0))
                nextState = MoveState::attack;
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
            if(input->fire && fireTimer <= sf::seconds(0))
                nextState = MoveState::attack;
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
        case MoveState::attack:
            if(fireTimer <= sf::seconds(0)) {
                fireTimer = sf::seconds(.5);
                unsigned int id = ComponentBase::getNewID();
                sf::Vector2f pos = position->getPosition();
                if(input->fireDir < 90 && input->fireDir > -90) pos.x+=40;
                else pos.x-=40;
                Entity* bullet = new Entity(id);
                int bulletSpeed = 10;
                bullet->setPosition(std::make_shared<WorldPositionComponent>(pos, position->getLayer(), (float)input->fireDir*0.0174532925));
                bullet->setRender(std::make_shared<StaticSpriteComponent>("assets/art/SuperMetroidSamus.png", sf::IntRect(423,29,16,6)));
                bullet->setPhysics(std::make_shared<SimpleBoxPhysics>(bullet->getID(), sf::Vector2f(10,5), 0, PhysicsOptions::isBullet | PhysicsOptions::sensor, bullet->getPosition()));
                bullet->getPhysics()->getBody()->SetLinearVelocity(b2Vec2(std::cos((float)input->fireDir*0.0174532925)*bulletSpeed, std::sin((float)input->fireDir*0.0174532925)*bulletSpeed));
                bullet->addScript(std::make_shared<KillScript>(true, 10, sf::Time::Zero));
                bullet->addScript(std::make_shared<ExplodeScript>());
                bullet->setMovement(std::make_shared<AccelerateMovement>(sf::Vector2f(std::cos((float)input->fireDir*0.0174532925)*bulletSpeed, std::sin((float)input->fireDir*0.0174532925)*bulletSpeed),100));
                ComponentManager::getInst().addEntity(id, bullet);
             }
             nextState = inAir;
        default:
            break;
        }
        fireTimer-=frameTime;
    }
}
