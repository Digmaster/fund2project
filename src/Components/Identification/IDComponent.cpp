#include "IDComponent.h"
#include "Components/ComponentManager.h"

IDComponent::~IDComponent()
{
    //dtor
}

IDComponent::IDComponent(unsigned int ID, std::string Name) : ComponentBase(ID)
{
    compMan->idSym.addComponent(this);
    name = Name;
}

void IDComponent::go(sf::Time frameTime) {

}
