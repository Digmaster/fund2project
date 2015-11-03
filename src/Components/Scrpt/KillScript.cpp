#include "Components/Script/KillScript.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "GameEngine.h"
#include "Components/Entity.h"

KillScript::KillScript(bool remove, int health, sf::Time freq) : remove(remove), frequency(freq), initFreq(freq), health(health), ScriptComponent()
{

}

KillScript::~KillScript()
{
    //dtor
}

void KillScript::go(sf::Time frameTime, Entity* entity)
{
    PhysicsComponent* phys = entity->getPhysics();
    if(frequency!=sf::Time::Zero)
    {
        if(frequency>sf::Time::Zero)
        {
            frequency -= frameTime;
        }
        else
        {
            frequency = sf::Time::Zero;
        }
    }
    if(phys!=nullptr) {
        if(phys->onRight() || phys->onLeft() || phys->onTop() || phys->onGround()) {
                StatsComponent* stats = nullptr;

            if(phys->onBody() && (*compMan)[phys->touchingBody()]!=nullptr)
                stats = (*compMan)[phys->touchingBody()]->getStats();
            if(phys->onRight() && (*compMan)[phys->touchingRight()]!=nullptr)
                stats = (*compMan)[phys->touchingRight()]->getStats();
            if(phys->onLeft() && (*compMan)[phys->touchingLeft()]!=nullptr)
                stats = (*compMan)[phys->touchingLeft()]->getStats();
            if(phys->onTop() && (*compMan)[phys->touchingTop()]!=nullptr)
                stats = (*compMan)[phys->touchingTop()]->getStats();
            if(phys->onGround() && (*compMan)[phys->touchingGround()]!=nullptr)
                stats = (*compMan)[phys->touchingGround()]->getStats();

            if(stats!=nullptr && frequency <= sf::Time::Zero) {
                frequency = initFreq;
                if(health==-1)
                    stats->setHealth(0);
                else
                    stats->modHealth(-health);
            }

            if(remove) {
                compMan->removeEntity(entity->getID());
            }
        }
    }
}
