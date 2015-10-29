#include "Component/Script/EnemySpawner.h"

#include "Components/Movement/EnemyMovement.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Input/InputComponent.h"
#include "Rendering/SpriteManager.h"
#include "Components/Render/StaticSpriteComponent.h"
#include "Components/Stats/StatsComponent.h"
#include "Components/Script/MainCharScript.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Entity.h"

EnemySpawner::EnemySpawner()
{
    //ctor
}

EnemySpawner::~EnemySpawner()
{
    //dtor
}

EnemySpawner::EnemySpawner(sf::Sprite spr, sf::Time frequency, int max, int range) : ScriptComponent(), spr(spr), freq(frequency), max(max), range(range) {
    countdown = frequency;
    curr = 0;
}

void EnemySpawner::go(sf::Time frameTime, Entity* entity) {
    unsigned int mainCharID = compMan->name2ID("MainChar");
    WorldPositionComponent* advPosComp = (*compMan)[mainCharID]->position;
    WorldPositionComponent* mePosComp = entity->position;
    countdown-=frameTime;
    if(advPosComp && mePosComp && curr <= max && countdown <= sf::seconds(0)) {
        int baddies = advPosComp->getPosition().x;
        int me = mePosComp->getPosition().x;
        int distance;
        if(baddies > me)
            distance = baddies-me;
        else
            distance = me-baddies;
        if(distance < range) {
            curr++;
            countdown = freq;
            unsigned int id = ComponentBase::getNewID();

            Entity* enemy = new Entity(id);
            enemy->render = new StaticSpriteComponent(spr);
            enemy->position = new WorldPositionComponent(*mePosComp);
            enemy->stats = new StatsComponent();
            enemy->scripts.push_back(new MainCharScript(false));
            enemy->movement = new EnemyMovement();
            enemy->physics = new SimpleBoxPhysics(id,sf::Vector2f(spr.getGlobalBounds().width,spr.getGlobalBounds().height),0, PhysicsOptions::roundedCorners | PhysicsOptions::notRotatable | PhysicsOptions::sideSensors, enemy->position);

            ComponentManager::getInst().addEntity(id, enemy);
        }
    }
}
