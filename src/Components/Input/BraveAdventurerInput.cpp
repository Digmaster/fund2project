#include "Components/Input/BraveAdventurerInput.h"
#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

BraveAdventurerInput::BraveAdventurerInput()
{
    //ctor
}

BraveAdventurerInput::~BraveAdventurerInput()
{
    //dtor
}

void BraveAdventurerInput::go(sf::Time) {
    MovementComponent* movement = ComponentManager::getInst().moveSym.getComponent(getID());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		movement->sendMessage("WalkUp");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		movement->sendMessage("WalkDown");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement->sendMessage("WalkLeft");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement->sendMessage("WalkRight");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        movement->sendMessage("Jump");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        movement->sendMessage("GoPlace");
	}
}
