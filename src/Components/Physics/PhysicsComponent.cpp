#include "Components/Physics/PhysicsComponent.h"
#include "Options.h"

b2World* PhysicsComponent::_world = NULL;
int PhysicsComponent::pixelsPerMeter = atoi(Options::instance().get("pixels_per_meter").c_str());

PhysicsComponent::~PhysicsComponent()
{
    //dtor
}
