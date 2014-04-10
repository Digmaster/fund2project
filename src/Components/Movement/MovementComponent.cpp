#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

MovementComponent::MovementComponent() : MovementComponent(0)
{
    //ctor
}

MovementComponent::MovementComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->moveSym.addComponent(this);
    currState = MoveState::onGround;
    nextState = MoveState::onGround;
}

MovementComponent::~MovementComponent()
{
    //dtor
}
