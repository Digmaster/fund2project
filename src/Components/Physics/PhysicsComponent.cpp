#include "Components/Physics/PhysicsComponent.h"
#include "Options.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "GameEngine.h"
#include "physics/PhysicsEngine.h"

PhysicsComponent::PhysicsComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->physSym.addComponent(this);
    physBody=NULL;
}

int PhysicsComponent::pixelsPerMeter = atoi(Options::instance().get("pixels_per_meter").c_str());

PhysicsComponent::~PhysicsComponent()
{
    eng->physEng->_world->DestroyBody(physBody);
}
