#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"

MovementComponent::MovementComponent() : ComponentBase() {
    currState = MoveState::onGround;
    nextState = MoveState::onGround;
    changed = false;
}

MovementComponent::~MovementComponent()
{
    //dtor
}
