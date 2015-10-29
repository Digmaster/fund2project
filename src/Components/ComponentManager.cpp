#include "Components/ComponentManager.h"
#include "Components/Entity.h"
#include "Components/Audio/AudioComponent.h"
#include "Components/Identification/IDComponent.h"
#include "Components/Input/InputComponent.h"
#include "Components/Movement/MovementComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/RenderComponent.h"
#include "Components/Script/ScriptComponent.h"
#include "Components/Stats/StatsComponent.h"
#include "Components/Target/TargetComponent.h"

ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 1;
    return ID++;
}

void ComponentManager::processAll(sf::Time frameTime) {
    std::cout << "now " << entities.size() << std::endl;
    for(std::unordered_map<int, Entity*>::iterator it = entities.begin(); it != entities.end();)
    {
        //Delete things to be deleted
        if(it->second->isDeleted())
        {
            delete it->second;
            it = entities.erase(it);
            continue;
        }

        Entity* entity = it->second;
        int ID = it->first;

        if(entity->audio!=nullptr)          entity->audio->go(frameTime, entity);
        if(entity->identification!=nullptr) entity->identification->go(frameTime, entity);
        if(entity->input!=nullptr)          entity->input->go(frameTime, entity);
        if(entity->movement!=nullptr)       entity->movement->go(frameTime, entity);
        if(entity->physics!=nullptr)        entity->physics->go(frameTime, entity);
        if(entity->position!=nullptr)       entity->position->go(frameTime, entity);
        if(entity->render!=nullptr)         entity->render->go(frameTime, entity);
        if(entity->stats!=nullptr)          entity->stats->go(frameTime, entity);
        if(entity->target!=nullptr)         entity->target->go(frameTime, entity);
        for(ScriptComponent* script : entity->scripts)
        {
            script->go(frameTime, entity);
        }
        it++;
    }
}

void ComponentManager::addEntity(int ID, Entity* entity)
{
    entities[ID] = entity;
}

void ComponentManager::removeEntity(int ID)
{
    entities[ID]->setDelete();
}

unsigned int ComponentManager::name2ID(std::string name) {
    auto entityIterator = std::find_if(entities.begin(), entities.end(), [name](std::pair<const int, Entity*> keyval){
                 return keyval.second->identification!=nullptr && keyval.second->identification->getName()==name;
                 });

    if(entityIterator!=entities.end())
        return entityIterator->first;
    else
        return 0;
}
