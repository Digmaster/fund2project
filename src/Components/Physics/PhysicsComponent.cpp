#include "Components/Physics/PhysicsComponent.h"
#include "Options.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"

PhysicsComponent::PhysicsComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->physSym.addComponent(this);
}

PhysicsEngine* PhysicsComponent::physEng = NULL;
int PhysicsComponent::pixelsPerMeter = atoi(Options::instance().get("pixels_per_meter").c_str());

PhysicsComponent::~PhysicsComponent()
{
    //dtor
}
