#include "Components/Script/MainCharScript.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "GameEngine.h"
#include <SFML/Audio.hpp>
#include "Components/Entity.h"
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

MainCharScript::MainCharScript(bool endGame, sf::Time time) : ScriptComponent()
{
    mainChar = endGame;
    deathCountDown = time;
}

MainCharScript::~MainCharScript()
{
    //dtor
}

void MainCharScript::go(sf::Time frameTime, Entity* entity)
{
    StatsComponent* stats = entity->stats;
    if(stats) {
        if(stats->isDead()) {
            if(mainChar==true)
                eng->playerDying=1;
            delete entity->input;
            delete entity->movement;
            delete entity->physics;
            entity->input = nullptr;
            entity->movement = nullptr;
            entity->physics = nullptr;
            deathCountDown -= frameTime; //Give everything time to play death animations and whatnot
            if(deathCountDown <= sf::seconds(0)) {
                compMan->removeEntity(entity->getID());
                if(mainChar) eng->playerDied();
            }
        }
    }
}
