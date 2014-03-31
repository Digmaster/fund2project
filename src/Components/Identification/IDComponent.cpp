#include "IDComponent.h"
#include "Components/ComponentManager.h"

IDComponent::~IDComponent()
{
    //dtor
}

IDComponent::IDComponent(unsigned int ID, std::string Name, std::string Type) : ComponentBase(ID)
{
    compMan->idSym.addComponent(this);
    name = Name;
    type = Type;
}

void IDComponent::go(sf::Time frameTime) {

}
