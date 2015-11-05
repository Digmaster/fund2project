#include "Components/Script/KillScript.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Identification/IDComponent.h"
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
    IDComponent* id = entity->getIdentification();
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
            Entity* enemy = nullptr;

            if(phys->onBody() && (*compMan)[phys->touchingBody()]!=nullptr)
                enemy = (*compMan)[phys->touchingBody()];
            if(phys->onRight() && (*compMan)[phys->touchingRight()]!=nullptr)
                enemy = (*compMan)[phys->touchingRight()];
            if(phys->onLeft() && (*compMan)[phys->touchingLeft()]!=nullptr)
                enemy = (*compMan)[phys->touchingLeft()];
            if(phys->onTop() && (*compMan)[phys->touchingTop()]!=nullptr)
                enemy = (*compMan)[phys->touchingTop()];
            if(phys->onGround() && (*compMan)[phys->touchingGround()]!=nullptr)
                enemy = (*compMan)[phys->touchingGround()];

            if(enemy!=nullptr && enemy->getStats()!=nullptr && frequency <= sf::Time::Zero) {
                StatsComponent* stats = enemy->getStats();
                IDComponent* enemyID = enemy->getIdentification();
                if(enemyID==nullptr || id==nullptr || enemyID->getFaction()!=id->getFaction() || enemyID->getFaction()=="")
                {
                    frequency = initFreq;
                    if(health==-1)
                        stats->setHealth(0, entity);
                    else
                        stats->modHealth(-health, entity);
                }
            }

            if(remove) {
                compMan->removeEntity(entity->getID());
            }
        }
    }
}
