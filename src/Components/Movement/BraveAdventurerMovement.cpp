#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Input/InputComponent.h"

using namespace std;

BraveAdventurerMovement::BraveAdventurerMovement()
{
    currMovement = "Still";
}

void BraveAdventurerMovement::go(sf::Time frameTime) {
    PhysicsComponent* physics = ComponentManager::getInst().physSym.getComponent(getID());
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    InputComponent* input = compMan->inputSym.getComponent(getID());
    if(physics!=NULL) {
        b2Body* body = physics->getBody();
        b2Vec2 velocity = body->GetLinearVelocity();
        if(input->walkLeft) {
            if(physics->onGround()) {
                body->ApplyLinearImpulse(b2Vec2(-3.0f-velocity.x*3.0f/15.0f,0),body->GetWorldCenter(),true);
            }
            else if(physics->onLeft()==false) {
                body->ApplyLinearImpulse(b2Vec2(-1.0f-velocity.x*1.0f/15.0f,0),body->GetWorldCenter(),true);
            }
            currMovement = "WalkLeft";
        }
        if(input->walkRight) {
            if(physics->onRight()==false) {
                if(physics->onGround())
                    body->ApplyLinearImpulse(b2Vec2(3.0f-velocity.x*3.0f/15.0f,0),body->GetWorldCenter(),true);
                else
                    body->ApplyLinearImpulse(b2Vec2(1.0f-velocity.x*1.0f/15.0f,0),body->GetWorldCenter(),true);
            }
            currMovement = "WalkRight";
        }
        if(input->climbUp){
            if(physics->overLadder()==true) {
                body->ApplyLinearImpulse(b2Vec2(0,1.0f-velocity.y*1.0f/15.0f),body->GetWorldCenter(),true);
            }
            currMovement = "ClimbUp";
        }
        if(input->climbDown){
            if(physics->overLadder()==true) {
                    body->ApplyLinearImpulse(b2Vec2(0,-1.0f-velocity.y*1.0f/15.0f),body->GetWorldCenter(),true);
            }
            currMovement = "ClimbDown";
        }
        if(input->jump) {
            if(physics->onGround()) {
                body->ApplyLinearImpulse(b2Vec2(0,6),body->GetWorldCenter(),true);
            }
            currMovement = "Jump";
        }
        if(input->activate)
            position->setPosition(sf::Vector2f(100,100));
        //cout << currMovement << endl;
    }
}
