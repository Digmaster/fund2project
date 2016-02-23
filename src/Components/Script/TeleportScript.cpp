#include "TeleportScript.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/ComponentManager.h"

TeleportScript::TeleportScript()
{
    //ctor
}

TeleportScript::~TeleportScript()
{
    //dtor
}

void TeleportScript::go(sf::Time frameTime, Entity* entity)
{

}

ComponentBase::listenerList TeleportScript::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&TeleportScript::HandleMessage, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::COLLISION, handler));
    return out;
}

void TeleportScript::HandleMessage(Events event, EventObj* message, Entity* entity)
{
    switch(event)
    {
    case COLLISION:
        Collision* obj = (Collision*)message;
        Entity* actor = ComponentManager::getInst()[obj->entity];
        if(actor!=nullptr && actor->getPosition()!=nullptr) {
            int targetID = entity->getTarget()->getTarget();
            Entity* target = ComponentManager::getInst()[targetID];
            std::cout << "Teleporting to " << targetID << std::endl;
            if(target!=nullptr && target->getPosition()!=nullptr)
            {
                actor->getPosition()->setPosition(target->getPosition()->getPosition(), actor->getPhysics().get(), true);
                actor->getPhysics()->getBody()->SetLinearVelocity(b2Vec2(0,0));
            }
        }
    }
}
