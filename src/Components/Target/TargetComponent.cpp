#include "TargetComponent.h"
#include "Components/ComponentManager.h"

TargetComponent::TargetComponent()
{
    //ctor
}

TargetComponent::~TargetComponent()
{
    //dtor
}

void TargetComponent::setTarget(std::string name)
{
    targetID = compMan->name2ID(name);
}

TargetComponent::TargetComponent(unsigned int ID, unsigned int target) : ComponentBase(ID) {
    compMan->targetSym.addComponent(this);
    setTarget(target);
}

TargetComponent::TargetComponent(unsigned int ID, std::string name) : ComponentBase(ID) {
    compMan->targetSym.addComponent(this);
    setTarget(name);
}
