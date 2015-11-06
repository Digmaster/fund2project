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
#include "Components/Script/EnemySpawner.h"
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

void Entity::addListener(std::type_index toListenTo, listener& toCall)
{
    componentListeners[toListenTo].push_back(toCall);
}

//void Entity::addListener(std::type_index toListenTo, ComponentBase* obj, unboundListener toCall)
//{
//    using namespace std::placeholders;
//    addListener(toListenTo, std::bind(toCall, *obj, _1, _2, _3));
//}

void Entity::removeListener(std::type_index toListenTo, listener& toCall)
{
    //componentListeners[toListenTo].remove(toCall);
}

void Entity::callListeners(std::type_index origin, Events event, EventObj* message)
{
    std::list<listener> toCall = componentListeners[origin];
    for(listener l : toCall)
    {
        l(event, message, this);
    }
}

Entity::~Entity()
{
//    delete audio;
//    delete identification;
//    delete input;
//    delete movement;
//    delete physics;
//    delete position;
//    delete render;
//    delete stats;
//    delete target;
}

void Entity::setAudio(AudioComponent* a) {setComponent(&audio, a);}
AudioComponent* Entity::getAudio() {return audio;}

void Entity::setRender(RenderComponent* a) {setComponent(&render, a);}
RenderComponent* Entity::getRender() {return render;}

void Entity::setIdentification(IDComponent* a) {setComponent(&identification, a);}
IDComponent* Entity::getIdentification() {return identification;}

void Entity::setInput(InputComponent* a) {setComponent(&input, a);}
InputComponent* Entity::getInput() {return input;}

void Entity::setMovement(MovementComponent* a) {setComponent(&movement, a);}
MovementComponent* Entity::getMovement() {return movement;}

void Entity::setPhysics(PhysicsComponent* a) {setComponent(&physics, a);}
PhysicsComponent* Entity::getPhysics() {return physics;}

void Entity::setPosition(WorldPositionComponent* a) {setComponent(&position, a);}
WorldPositionComponent* Entity::getPosition() {return position;}

void Entity::setStats(StatsComponent* a) {setComponent(&stats, a);}
StatsComponent* Entity::getStats() {return stats;}

void Entity::setTarget(TargetComponent* a) {setComponent(&target, a);}
TargetComponent* Entity::getTarget() {return target;}

template<typename T>
void Entity::setComponent(T** o, T* n)
{
    if((*o) != nullptr)
        (*o)->removeListeners(this);
    if(n != nullptr)
        n->setUpListeners(this);
    *o = n;
}
