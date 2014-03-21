#include "Components/Input/DumbKeyboardInputComponent.h"
#include "Components/ComponentManager.h"

DumbKeyboardInputComponent::DumbKeyboardInputComponent()
{
	//ctor
}

void DumbKeyboardInputComponent::go(sf::Time)
{
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//currentAnimation = &walkingAnimationUp;
		//currAnimation="WalkUp";
		position->move(sf::Vector2f(0,-5));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//currentAnimation = &walkingAnimationDown;
		//currAnimation="WalkDown";
		position->move(sf::Vector2f(0,5));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//currentAnimation = &walkingAnimationLeft;
		//currAnimation="WalkLeft";
		position->move(sf::Vector2f(-5,0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//currentAnimation = &walkingAnimationRight;
		//currAnimation="WalkRight";
		position->move(sf::Vector2f(5,0));
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		animatedSprite.setSpeed(2);
		speed = 160.f;
	}*/
}
