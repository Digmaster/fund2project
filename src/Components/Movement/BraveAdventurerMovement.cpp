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
            //if(message == "WalkUp")
                //position->move(sf::Vector2f(0,-2));
            //if(message == "WalkDown")
                //position->move(sf::Vector2f(0,2));
            if(message == "WalkLeft")
                body->SetLinearVelocity(b2Vec2(-5,velocity.y));
                //position->move(sf::Vector2f(-2,0));
            if(message == "WalkRight")
                body->SetLinearVelocity(b2Vec2(5,velocity.y));
                //position->move(sf::Vector2f(2,0));
            if(message == "Jump")
                body->ApplyLinearImpulse(b2Vec2(0,2),body->GetWorldCenter(),true);
            if(message == "GoPlace")
                position->setPosition(sf::Vector2f(100,100));
        }
        currMovement = message;
        message = getMessage();
    }
}
