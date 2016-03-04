#include "KeyboardInput.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Rendering/RenderEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include "InputEngine.h"
#include "GameEngine.h"

KeyboardInput::KeyboardInput() : InputComponent() {
    walkLeft=eng->inputEng->getWalkLeft();
    walkRight=eng->inputEng->getWalkRight();
    climbUp=eng->inputEng->getClimbUp();
    climbDown=eng->inputEng->getClimbDown();
    fire=eng->inputEng->getFire();
    jump=eng->inputEng->getJump();
    activate=eng->inputEng->getActivate();
    currWeapon=eng->inputEng->getCurrWeapon();
    mouseX = eng->inputEng->getMousePos().x;
    mouseY = eng->inputEng->getMousePos().y;
}

KeyboardInput::~KeyboardInput()
{
    //dtor
}

void KeyboardInput::go(sf::Time, Entity* entity) {
    walkLeft=eng->inputEng->getWalkLeft();
    walkRight=eng->inputEng->getWalkRight();
    climbUp=eng->inputEng->getClimbUp();
    climbDown=eng->inputEng->getClimbDown();
    fire=eng->inputEng->getFire();
    jump=eng->inputEng->getJump();
    activate=eng->inputEng->getActivate();
    currWeapon=eng->inputEng->getCurrWeapon();
    mouseX = eng->inputEng->getMousePos().x;
    mouseY = eng->inputEng->getMousePos().y;
    std::shared_ptr<WorldPositionComponent> posComp = entity->getPosition();
    if(posComp)
        fireDir=eng->inputEng->getMouseAngle(posComp->getPosition());
}

void KeyboardInput::addKeyboardListener(KeyboardEvent event, InputEngine::keyboardListener listener)
{
    InputEngine::keyboardListenerList::iterator it = eng->inputEng->addListener(event, listener);
    subscribedEvents.push_back(it);
}
