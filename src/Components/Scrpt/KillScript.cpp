#include "Components/Script/KillScript.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "GameEngine.h"
#include "Components/Entity.h"

KillScript::KillScript(bool remove, int health, sf::Time freq) : remove(remove), frequency(freq), health(health), ScriptComponent()
{

}

KillScript::~KillScript()
{
    //dtor
}

void KillScript::go(sf::Time frameTime, Entity* entity)
{
    PhysicsComponent* phys = entity->physics;
    if(phys!=nullptr) {
        if(phys->onRight() || phys->onLeft() || phys->onTop() || phys->onGround()) {
                StatsComponent* stats;

            if(phys->onRight() && (*compMan)[phys->touchingRight()]!=nullptr)
                stats = (*compMan)[phys->touchingRight()]->stats;
            if(phys->onLeft() && (*compMan)[phys->touchingLeft()]!=nullptr)
                stats = (*compMan)[phys->touchingLeft()]->stats;
            if(phys->onTop() && (*compMan)[phys->touchingTop()]!=nullptr)
                stats = (*compMan)[phys->touchingTop()]->stats;
            if(phys->onGround() && (*compMan)[phys->touchingGround()]!=nullptr)
                stats = (*compMan)[phys->touchingGround()]->stats;
            if(stats) {
                stats->setHealth(0);
            }
            if(remove) {
                compMan->removeEntity(entity->getID());
            }
        }
    }
}
