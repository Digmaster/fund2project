#include "ExplodeScript.h"
#include <SFML/Graphics.hpp>

#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/SingleUseAnimatedComponent.h"
#include "Components/ComponentManager.h"

ExplodeScript::ExplodeScript()
{
    //ctor
}

ExplodeScript::~ExplodeScript()
{
    //dtor
}

ComponentBase::listenerList ExplodeScript::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&ExplodeScript::HandleMessage, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::DELETED, handler));
    return out;
}

void ExplodeScript::HandleMessage(Events event, EventObj* message, Entity* entity)
{
    switch(event)
    {
    case DELETED:
        unsigned int id = ComponentBase::getNewID();
        sf::Vector2f pos = entity->getPosition()->getPosition();
        Entity* bullet = new Entity(id);
        bullet->setPosition(std::make_shared<WorldPositionComponent>(pos, entity->getPosition()->getLayer()));
        bullet->setRender(std::make_shared<SingleUseAnimatedComponent>("Explosion", "Explode"));
        ComponentManager::getInst().addEntity(id, bullet);
    }
}
