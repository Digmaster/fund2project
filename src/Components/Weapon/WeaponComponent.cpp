#include "WeaponComponent.h"

#include "Components/Identification/IDComponent.h"

WeaponComponent::WeaponComponent()
{
    //ctor
}

void WeaponComponent::go(sf::Time frameTime,  Entity* entity)
{
    fireTimer -= frameTime;
}
