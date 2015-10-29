#include "Components/Physics/PhysicsComponent.h"
#include "Options.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "GameEngine.h"
#include "physics/PhysicsEngine.h"

PhysicsComponent::PhysicsComponent() : ComponentBase() {
    physBody=NULL;
}

int PhysicsComponent::pixelsPerMeter = atoi(Options::instance().get("pixels_per_meter").c_str());

PhysicsComponent::~PhysicsComponent()
{
    physBody->GetWorld()->DestroyBody(physBody);
}
