#include "Components/Stats/StatsComponent.h"

#include "Components/ComponentManager.h"

StatsComponent::StatsComponent() : StatsComponent(0)
{

}

StatsComponent::StatsComponent(unsigned int ID, int health) : ComponentBase(ID)
{
    health = health;
    dead = false;
    compMan->statSym.addComponent(this);
}

StatsComponent::~StatsComponent()
{
    //dtor
}

void StatsComponent::go(sf::Time frameTime)
{
    //Currently not used
}
int StatsComponent::getHealth()
{
    return health;
}

void StatsComponent::setHealth(int input)
{
    health = input;
    if(health>0) dead = false;
    if(health<=0) dead = true;
}

void StatsComponent::modHealth(int input)
{
    setHealth(health+input);
}

bool StatsComponent::isDead()
{
    return dead;
}
