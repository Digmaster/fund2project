#include "Components/Entity.h"
#include <iostream>

#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/StaticSpriteComponent.h"
#include "Rendering/RenderEngine.h"
#include "Components/Identification/IDComponent.h"
#include "Components/Script/Camera.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Movement/BraveAdventurerMovement.h"
#include "Rendering/SpriteManager.h"
#include "Components/Physics/BoundaryPhysics.h"
#include "Components/Input/KeyboardInput.h"
#include "Components/Physics/PolygonPhysics.h"
#include "Components/Physics/PolylinePhysics.h"
#include "Components/Audio/AudioComponent.h"
#include "Components/Movement/EnemyMovement.h"
#include "Components/Stats/StatsComponent.h"
#include "Components/Script/MainCharScript.h"
#include "Component/Script/EnemySpawner.h"
#include "Components/Script/KillScript.h"

Entity::Entity(int ID) : _ID(ID)
{
    audio = nullptr;
    identification = nullptr;
    input = nullptr;
    movement = nullptr;
    physics = nullptr;
    position = nullptr;
    render = nullptr;
    stats = nullptr;
    target = nullptr;
    _delete = false;
}

void Entity::addListener(std::type_index toListenTo, listener toCall)
{
    componentListeners[toListenTo].push_back(toCall);
}

//void Entity::addListener(std::type_index toListenTo, ComponentBase* obj, unboundListener toCall)
//{
//    using namespace std::placeholders;
//    addListener(toListenTo, std::bind(toCall, *obj, _1, _2, _3));
//}

void Entity::removeListener(std::type_index toListenTo, listener toCall)
{
    //componentListeners[toListenTo].remove(toCall);
}

void Entity::callListeners(std::type_index origin, Events event, std::vector<std::string> message)
{
    std::list<listener> toCall = componentListeners[origin];
    for(listener l : toCall)
    {
        l(event, message, this);
    }
}

Entity::~Entity()
{
    delete audio;
    delete identification;
    delete input;
    delete movement;
    delete physics;
    delete position;
    delete render;
    delete stats;
    delete target;
}

void Entity::setAudio(AudioComponent* a) {audio = a; if(a) a->setUpListeners(this);}
AudioComponent* Entity::getAudio() {return audio;}

void Entity::setRender(RenderComponent* a) {render = a; if(a) a->setUpListeners(this);}
RenderComponent* Entity::getRender() {return render;}

void Entity::setIdentification(IDComponent* a) {identification = a; if(a) a->setUpListeners(this);}
IDComponent* Entity::getIdentification() {return identification;}

void Entity::setInput(InputComponent* a) {input = a; if(a) a->setUpListeners(this);}
InputComponent* Entity::getInput() {return input;}

void Entity::setMovement(MovementComponent* a) {movement = a; if(a) a->setUpListeners(this);}
MovementComponent* Entity::getMovement() {return movement;}

void Entity::setPhysics(PhysicsComponent* a) {physics = a; if(a) a->setUpListeners(this);}
PhysicsComponent* Entity::getPhysics() {return physics;}

void Entity::setPosition(WorldPositionComponent* a) {position = a; if(a) a->setUpListeners(this);}
WorldPositionComponent* Entity::getPosition() {return position;}

void Entity::setStats(StatsComponent* a) {stats = a; if(a) a->setUpListeners(this);}
StatsComponent* Entity::getStats() {return stats;}

void Entity::setTarget(TargetComponent* a) {target = a; if(a) a->setUpListeners(this);}
TargetComponent* Entity::getTarget() {return target;}
