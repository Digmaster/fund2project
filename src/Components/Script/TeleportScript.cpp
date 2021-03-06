#include "TeleportScript.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/ComponentManager.h"
#include "GameEngine.h"
#include "Physics/PhysicsEngine.h"
#include "Options.h"

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
#include <Box2D/Box2D.h>
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
            if(target!=nullptr && target->getPosition()!=nullptr)
            {
                actor->getPosition()->setPosition(target->getPosition()->getPosition(), actor->getPhysics().get(), true);
                actor->getPhysics()->getBody()->SetLinearVelocity(b2Vec2(0,0));
                float targetHeight = 3;
                float springConstant = 100;

                //make the ray at least as long as the target distance
                b2Vec2 startOfRay = actor->getPhysics()->getBody()->GetPosition();
                startOfRay.y -= 1;

                b2Vec2 endOfRay = actor->getPhysics()->getBody()->GetWorldPoint( b2Vec2(0,-5) );

                HovercarRayCastClosestCallback callback;
                eng->physEng->_world->RayCast(&callback, startOfRay, endOfRay);

                if ( callback.m_hit ) {
                    float distanceAboveGround = (startOfRay - callback.m_point).Length();
                    distanceAboveGround *= Options::instance().getPixelsPerMeter();
                    std::cout << distanceAboveGround << std::endl;
                    actor->getPosition()->move(sf::Vector2f(0, distanceAboveGround), actor->getPhysics().get());
                }
            }
        }
    }
}
