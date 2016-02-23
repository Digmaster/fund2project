#include "Components/ComponentBase.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"
#include <iostream>

ComponentManager* ComponentBase::compMan = &ComponentManager::getInst();
RenderEngine* ComponentBase::rendEng = NULL;
GameEngine* ComponentBase::eng = NULL;

ComponentBase::ComponentBase()
{
}

unsigned int ComponentBase::getNewID() {
    return ComponentManager::getNewID();
}

void ComponentBase::setUpListeners(Entity* entity)
{
    _entitiesToCall.push_back(entity);
    auto listeners = getListeners();
    for(auto it = listeners.begin(); it != listeners.end(); it++)
    {
        entity->addListener(it->first, it->second);
    }
}

void ComponentBase::removeListeners(Entity* entity)
{
    _entitiesToCall.remove(entity);
    auto listeners = getListeners();
    for(auto it = listeners.begin(); it != listeners.end(); it++)
    {
        entity->removeListener(it->first, it->second);
    }
}

void ComponentBase::callListeners(Events event, EventObj* message)
{
    for(auto entity : _entitiesToCall)
    {
        entity->callListeners(event, message);
    }
}
