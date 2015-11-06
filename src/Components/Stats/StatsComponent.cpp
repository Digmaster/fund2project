#include "Components/Stats/StatsComponent.h"

#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include<string>

StatsComponent::StatsComponent(int health) : ComponentBase()
{
    this->health = health;
    dead = false;
    speedMod = 1;
    runMod = 1;
}

StatsComponent::~StatsComponent()
{
    //dtor
}

void StatsComponent::go(sf::Time frameTime, Entity* entity)
{

}

int StatsComponent::getHealth()
{
    return health;
}

void StatsComponent::setHealth(int input, Entity* causer)
{
    callListeners(typeid(StatsComponent), Events::HEALTH_CHANGE, new HealthChange(health-input, input, health, causer));
    health = input;
    if(health>0)
    {
        dead = false;
    }
    if(health<=0)
        dead = true;

    if(dead)
        callListeners(typeid(StatsComponent), Events::DEATH);
}

void StatsComponent::modHealth(int input, Entity* causer)
{
    setHealth(health+input, causer);
}

bool StatsComponent::isDead()
{
    return dead;
}
