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

void Entity::setAudio(std::shared_ptr<AudioComponent> a) {setComponent(&audio, a);}
std::shared_ptr<AudioComponent> Entity::getAudio() {return audio;}

void Entity::setRender(std::shared_ptr<RenderComponent> a) {setComponent(&render, a);}
std::shared_ptr<RenderComponent> Entity::getRender() {return render;}

void Entity::setIdentification(std::shared_ptr<IDComponent> a) {setComponent(&identification, a);}
std::shared_ptr<IDComponent> Entity::getIdentification() {return identification;}

void Entity::setInput(std::shared_ptr<InputComponent> a) {setComponent(&input, a);}
std::shared_ptr<InputComponent> Entity::getInput() {return input;}

void Entity::setMovement(std::shared_ptr<MovementComponent> a) {setComponent(&movement, a);}
std::shared_ptr<MovementComponent> Entity::getMovement() {return movement;}

void Entity::setPhysics(std::shared_ptr<PhysicsComponent> a) {setComponent(&physics, a);}
std::shared_ptr<PhysicsComponent> Entity::getPhysics() {return physics;}

void Entity::setPosition(std::shared_ptr<WorldPositionComponent> a) {setComponent(&position, a);}
std::shared_ptr<WorldPositionComponent> Entity::getPosition() {return position;}

void Entity::setStats(std::shared_ptr<StatsComponent> a) {setComponent(&stats, a);}
std::shared_ptr<StatsComponent> Entity::getStats() {return stats;}

void Entity::setTarget(std::shared_ptr<TargetComponent> a) {setComponent(&target, a);}
std::shared_ptr<TargetComponent> Entity::getTarget() {return target;}

template<typename T>
void Entity::setComponent(T* o, T n)
{
    if((*o) != nullptr)
        (*o)->removeListeners(this);
    if(n != nullptr)
        n->setUpListeners(this);
    *o = n;
}
