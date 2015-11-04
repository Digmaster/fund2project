#include "IDComponent.h"
#include "Components/ComponentManager.h"

IDComponent::~IDComponent()
{
    //dtor
}

IDComponent::IDComponent(std::string Name, std::string Type, std::string Faction) : ComponentBase()
{
    name = Name;
    type = Type;
    faction = Faction;
}

void IDComponent::go(sf::Time frameTime, Entity* entity) {

}
