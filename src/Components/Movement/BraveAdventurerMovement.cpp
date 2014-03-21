#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"

using namespace std;

BraveAdventurerMovement::BraveAdventurerMovement()
{
    currMovement = "Still";
}

void BraveAdventurerMovement::go(sf::Time frameTime) {
    string message = getMessage();
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    if(message == "NOMESSAGE")
        currMovement = "none";
    while(message!="NOMESSAGE") {
        if(position!=NULL) {
            if(message == "WalkUp")
                position->move(sf::Vector2f(0,-2));
            if(message == "WalkDown")
                position->move(sf::Vector2f(0,2));
            if(message == "WalkLeft")
                position->move(sf::Vector2f(-2,0));
            if(message == "WalkRight")
                position->move(sf::Vector2f(2,0));
        }
        currMovement = message;
        message = getMessage();
    }
}
