#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

MovementComponent::MovementComponent() : ComponentBase()
{
    //ctor
}

MovementComponent::MovementComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->moveSym.addComponent(this);
}

MovementComponent::~MovementComponent()
{
    //dtor
}
