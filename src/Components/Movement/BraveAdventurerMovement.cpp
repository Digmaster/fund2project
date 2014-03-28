#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"

using namespace std;

BraveAdventurerMovement::BraveAdventurerMovement()
{
    currMovement = "Still";
}

void BraveAdventurerMovement::go(sf::Time frameTime) {
    string message = getMessage();
    PhysicsComponent* physics = ComponentManager::getInst().physSym.getComponent(getID());
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    if(message == "NOMESSAGE")
        currMovement = "none";
    while(message!="NOMESSAGE") {
        if(physics!=NULL) {
            b2Body* body = physics->getBody();
            b2Vec2 velocity = body->GetLinearVelocity();

            /* TODO (Thomas Luppi#1#03/27/14): Use force instead of impulse here, should work better? */

            if(message == "WalkLeft")
                if(physics->onGround()) {
                    body->ApplyLinearImpulse(b2Vec2(-3.0f-velocity.x*3.0f/15.0f,0),body->GetWorldCenter(),true);
                }
                else if(physics->onLeft()==false) {
                    body->ApplyLinearImpulse(b2Vec2(-1.0f-velocity.x*1.0f/15.0f,0),body->GetWorldCenter(),true);
                }

                //position->move(sf::Vector2f(-2,0));
            if(message == "WalkRight")
                if(physics->onRight()==false) {
                    if(physics->onGround())
                        body->ApplyLinearImpulse(b2Vec2(3.0f-velocity.x*3.0f/15.0f,0),body->GetWorldCenter(),true);
                    else
                        body->ApplyLinearImpulse(b2Vec2(1.0f-velocity.x*1.0f/15.0f,0),body->GetWorldCenter(),true);
                }
                //position->move(sf::Vector2f(2,0));
            if(message == "Jump")
                if(physics->onGround()) {
                    body->ApplyLinearImpulse(b2Vec2(0,6),body->GetWorldCenter(),true);
                }
            if(message == "GoPlace")
                position->setPosition(sf::Vector2f(100,100));
        }
        currMovement = message;
        message = getMessage();
    }
}
