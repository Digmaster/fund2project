#include "TargetComponent.h"
#include "Components/ComponentManager.h"

TargetComponent::~TargetComponent()
{
    //dtor
}

void TargetComponent::setTarget(std::string name)
{
    targetID = compMan->name2ID(name);
}

TargetComponent::TargetComponent(unsigned int target) : ComponentBase() {
    setTarget(target);
}

TargetComponent::TargetComponent(std::string name) : ComponentBase() {
    targetID=0;
    this->name = name;
}

void TargetComponent::go(sf::Time frameTime, Entity* entity)
{
    if(name!="none") {
        setTarget(name);
        name = "none";
    }
}
