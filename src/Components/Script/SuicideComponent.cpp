#include "SuicideComponent.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Identification/IDComponent.h"
#include "GameEngine.h"
#include "Components/Entity.h"

SuicideComponent::SuicideComponent(sf::Time timeToDie) : timeToDie(timeToDie), ScriptComponent()
{

}

SuicideComponent::~SuicideComponent()
{
    //dtor
}

void SuicideComponent::go(sf::Time frameTime, Entity* entity)
{
    timeToDie -= frameTime;
    if(timeToDie <= sf::Time::Zero)
    {
        compMan->removeEntity(entity->getID());
    }
}
