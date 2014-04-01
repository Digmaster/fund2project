#include "KeyboardInput.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Rendering/RenderEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "InputEngine.h"
#include "GameEngine.h"

KeyboardInput::KeyboardInput(unsigned int ID) : InputComponent(ID) {
    walkLeft=eng->inputEng->getWalkLeft();
    walkRight=eng->inputEng->getWalkRight();
    climbUp=eng->inputEng->getClimbUp();
    climbDown=eng->inputEng->getClimbDown();
    fire=eng->inputEng->getFire();
    jump=eng->inputEng->getJump();
    activate=eng->inputEng->getActivate();
    currWeapon=0;
    mouseX = eng->inputEng->getMouseX();
    mouseY = eng->inputEng->getMouseY();
    WorldPositionComponent* posComp = compMan->posSym.getComponent(getID());
    if(posComp)
        fireDir=eng->inputEng->getMouseAngle(posComp->getPosition());
}

KeyboardInput::~KeyboardInput()
{
    //dtor
}

void KeyboardInput::go(sf::Time) {
    walkLeft=eng->inputEng->getWalkLeft();
    walkRight=eng->inputEng->getWalkRight();
    climbUp=eng->inputEng->getClimbUp();
    climbDown=eng->inputEng->getClimbDown();
    fire=eng->inputEng->getFire();
    jump=eng->inputEng->getJump();
    activate=eng->inputEng->getActivate();
    currWeapon=0;
    mouseX = eng->inputEng->getMouseX();
    mouseY = eng->inputEng->getMouseY();
    WorldPositionComponent* posComp = compMan->posSym.getComponent(getID());
    if(posComp)
        fireDir=eng->inputEng->getMouseAngle(posComp->getPosition());
    //cout << mouseY << " " << mouseX << " " << posComp->getPosition().x << " " << posComp->getPosition().y << endl;
}
