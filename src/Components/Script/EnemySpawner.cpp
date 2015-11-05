#include "Components/Script/EnemySpawner.h"

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
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Input/BasicAIInput.h"
#include "Components/Script/KillScript.h"
#include "Components/Audio/AudioComponent.h"

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
    WorldPositionComponent* advPosComp = (*compMan)[mainCharID]->getPosition();
    WorldPositionComponent* mePosComp = entity->getPosition();
    countdown-=frameTime;
    if(advPosComp && mePosComp && (max==-1 || curr < max) && countdown <= sf::seconds(0)) {
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

            enemy->setPosition(new WorldPositionComponent(*mePosComp));

            SpriteManager spriteMan;
            BraveAdventurerAnimatedComponent* testSprite = new BraveAdventurerAnimatedComponent();
            testSprite->setSprite(spriteMan.getSprite("Samus"));
            enemy->setRender(testSprite);

            enemy->setMovement(new BraveAdventurerMovement());
            enemy->setInput(new BasicAIInput());
            enemy->setStats(new StatsComponent(20));
            enemy->getStats()->setSpeed(.5);
            enemy->addScript(new MainCharScript(false, sf::seconds(.5)));
            enemy->addScript(new KillScript(false, 10, sf::seconds(.5)));
            enemy->setAudio(new AudioComponent());
            enemy->setIdentification(new IDComponent("","","enemy"));

            enemy->setPhysics(new SimpleBoxPhysics(id,sf::Vector2f(34,42),0, PhysicsOptions::roundedCorners | PhysicsOptions::notRotatable | PhysicsOptions::sideSensors, enemy->getPosition()));

            ComponentManager::getInst().addEntity(id, enemy);
        }
    }
}
