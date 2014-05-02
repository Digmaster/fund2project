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

EnemySpawner::EnemySpawner()
{
    //ctor
}

EnemySpawner::~EnemySpawner()
{
    //dtor
}

EnemySpawner::EnemySpawner(unsigned int id, sf::Sprite spr, sf::Time frequency, int max, int range) : ScriptComponent(id), spr(spr), freq(frequency), max(max), range(range) {
    countdown = frequency;
    curr = 0;
}

void EnemySpawner::go(sf::Time frameTime) {
    unsigned int mainCharID = compMan->name2ID("MainChar");
    WorldPositionComponent* advPosComp = compMan->posSym.getComponent(mainCharID);
    WorldPositionComponent* mePosComp = compMan->posSym.getComponent(getID());
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
            //BraveAdventurerAnimatedComponent* testSprite = new BraveAdventurerAnimatedComponent(id);
            SpriteManager spriteMan;

            //testSprite->setSprite(spriteMan.getSprite("Samus"));

            new StaticSpriteComponent(spr, id);
            new WorldPositionComponent(id, mePosComp->getPosition(), mePosComp->getLayer());

            //KeyboardInput* testInput = new KeyboardInput(id);

            EnemyMovement* testMovement = new EnemyMovement(id);
            new StatsComponent(id);
            new MainCharScript(id, false);

            SimpleBoxPhysics* testPhys = new SimpleBoxPhysics(id,sf::Vector2f(spr.getGlobalBounds().width,spr.getGlobalBounds().height),0, PhysicsOptions::roundedCorners | PhysicsOptions::notRotatable | PhysicsOptions::sideSensors);
        }
    }
}
