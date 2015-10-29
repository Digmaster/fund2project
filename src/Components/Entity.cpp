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
