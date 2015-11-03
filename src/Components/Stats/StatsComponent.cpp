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

void StatsComponent::setHealth(int input)
{
    if(_listenedEntity) _listenedEntity->callListeners(typeid(StatsComponent), Events::HEALTH_CHANGE, {patch::to_string(health), patch::to_string(input)});
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

void StatsComponent::modHealth(int input)
{
    setHealth(health+input);
}

bool StatsComponent::isDead()
{
    return dead;
}
