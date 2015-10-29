#include "Components/Input/InputComponent.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"

InputComponent::InputComponent() : ComponentBase() {
    walkLeft=false;
    walkRight=false;
    climbUp=false;
    climbDown=false;
    fire=false;
    jump=false;
    activate=false;
    currWeapon=0;
    mouseX = sf::Mouse::getPosition(rendEng->window).x;
    mouseY = sf::Mouse::getPosition(rendEng->window).y;
    fireDir=0;
}

InputComponent::~InputComponent() {

}
