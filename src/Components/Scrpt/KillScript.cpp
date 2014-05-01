#include "Components/Script/KillScript.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "GameEngine.h"

KillScript::KillScript() : KillScript(0)
{

}

KillScript::KillScript(unsigned int ID, int health, sf::Time freq) : frequency(freq), health(health), ScriptComponent(ID)
{

}

KillScript::~KillScript()
{
    //dtor
}

void KillScript::go(sf::Time frameTime)
{
    PhysicsComponent* phys = compMan->physSym.getComponent(getID());
    if(phys) {
        if(phys->onRight() || phys->onLeft() || phys->onTop() ||phys->onGround()) {
                StatsComponent* stats;
            if(phys->onRight())
                stats = compMan->statSym.getComponent(phys->touchingRight());
            if(phys->onLeft())
                stats = compMan->statSym.getComponent(phys->touchingLeft());
            if(phys->onTop())
                stats = compMan->statSym.getComponent(phys->touchingTop());
            if(phys->onGround())
                stats = compMan->statSym.getComponent(phys->touchingGround());
            if(stats) {
                stats->setHealth(0);
            }
            compMan->moveSym.removeComponent(getID()); //Remove movement
            compMan->inputSym.removeComponent(getID()); //input
            compMan->physSym.removeComponent(getID()); //physics
            compMan->audioSym.removeComponent(getID());
            compMan->idSym.removeComponent(getID());
            compMan->posSym.removeComponent(getID());
            compMan->rendSym.removeComponent(getID());
            compMan->statSym.removeComponent(getID());
            compMan->targetSym.removeComponent(getID());
            compMan->scriptSym.removeComponent(getID()); //Oh god, remove self
        }
    }
}
