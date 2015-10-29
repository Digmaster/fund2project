#include "IDComponent.h"
#include "Components/ComponentManager.h"

IDComponent::~IDComponent()
{
    //dtor
}

IDComponent::IDComponent(std::string Name, std::string Type) : ComponentBase()
{
    name = Name;
    type = Type;
}

void IDComponent::go(sf::Time frameTime, Entity* entity) {

}
