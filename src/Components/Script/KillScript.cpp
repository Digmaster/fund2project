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

}

ComponentBase::listenerList KillScript::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&KillScript::HandleMessage, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::COLLISION, handler));
    return out;
}

void KillScript::HandleMessage(Events event, EventObj* message, Entity* entity)
{
    std::shared_ptr<IDComponent> id = entity->getIdentification();
    switch(event)
    {
    case COLLISION:
        Collision* obj = (Collision*)message;
        if(obj->otherHit->IsSensor()) return; //don't react to sensors

        bool shouldRemove = true;

        Entity* actor = ComponentManager::getInst()[obj->entity];
        if(actor!=nullptr && actor->getStats()!=nullptr && frequency <= sf::Time::Zero) {
            std::shared_ptr<StatsComponent> stats = actor->getStats();
            std::shared_ptr<IDComponent> enemyID = actor->getIdentification();
            if(enemyID==nullptr || id==nullptr || enemyID->getFaction()!=id->getFaction() || enemyID->getFaction()=="")
            {
                frequency = initFreq;
                if(health==-1)
                    stats->setHealth(0, actor);
                else
                    stats->modHealth(-health, actor);

            }
            else
            {
                shouldRemove = false;
            }
        }

        if(remove && shouldRemove) {
            compMan->removeEntity(entity->getID());
        }
    }
}
