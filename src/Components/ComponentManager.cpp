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
#include "Components/Script/Camera.h"

ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 1;
    return ID++;
}

void ComponentManager::processAll(sf::Time frameTime) {
    for(std::unordered_map<int, Entity*>::iterator it = entities.begin(); it != entities.end();)
    {
        //Delete things to be deleted
        if(it->second->isDeleted())
        {
            it++;
            continue;
        }

        Entity* entity = it->second;
        int ID = it->first;
        entity->update(frameTime);
        it++;
    }
    for(std::unordered_map<int, Entity*>::iterator it = entities.begin(); it != entities.end();)
    {
        //Delete things to be deleted
        if(it->second->isDeleted())
        {
            std::cout << "Deleting Entity: " << it->first << std::endl;
            delete it->second;
            it = entities.erase(it);
            continue;
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
    entities[ID]->callListeners(Events::DELETED);
    entities[ID]->setDelete();
}

unsigned int ComponentManager::name2ID(std::string name) {
    auto entityIterator = std::find_if(entities.begin(), entities.end(), [name](std::pair<const int, Entity*> keyval){
                 return keyval.second->getIdentification()!=nullptr && keyval.second->getIdentification()->getName()==name;
                 });

    if(entityIterator!=entities.end())
        return entityIterator->first;
    else
        return 0;
}
