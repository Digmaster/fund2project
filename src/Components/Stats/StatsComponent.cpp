#include "Components/Stats/StatsComponent.h"

#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include<string>

StatsComponent::StatsComponent(int health) : ComponentBase()
{
    this->health = health;
    dead = false;
}

StatsComponent::~StatsComponent()
{
    //dtor
}

void StatsComponent::go(sf::Time frameTime, Entity* entity)
{

}

void StatsComponent::setUpListeners(Entity* entity)
{
    _listenedEntity = entity;
    speedMod = 1;
    runMod = 1;
}

int StatsComponent::getHealth()
{
    return health;
}

void StatsComponent::setHealth(int input, Entity* causer)
{
    if(_listenedEntity) _listenedEntity->callListeners(typeid(StatsComponent), Events::HEALTH_CHANGE, new HealthChange(health-input, input, health, causer));
    health = input;
    if(health>0)
    {
        dead = false;
    }
    if(health<=0)
        dead = true;

    if(dead)
        _listenedEntity->callListeners(typeid(StatsComponent), Events::DEATH);
}

void StatsComponent::modHealth(int input, Entity* causer)
{
    setHealth(health+input, causer);
}

bool StatsComponent::isDead()
{
    return dead;
}
