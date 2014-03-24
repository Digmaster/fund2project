#include "Components/Input/InputComponent.h"
#include "Components/ComponentManager.h"

InputComponent::InputComponent()
{
    //ctor
}

InputComponent::InputComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->inputSym.addComponent(this);
}

InputComponent::~InputComponent() {

}
