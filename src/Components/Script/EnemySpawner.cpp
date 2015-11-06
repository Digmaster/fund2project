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
    std::shared_ptr<WorldPositionComponent> advPosComp = (*compMan)[mainCharID]->getPosition();
    std::shared_ptr<WorldPositionComponent> mePosComp = entity->getPosition();
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

            enemy->setPosition(std::make_shared<WorldPositionComponent>(*mePosComp));

            SpriteManager spriteMan;
            std::shared_ptr<BraveAdventurerAnimatedComponent> testSprite = std::make_shared<BraveAdventurerAnimatedComponent>();
            testSprite->setSprite(spriteMan.getSprite("Samus"));
            enemy->setRender(testSprite);

            enemy->setMovement(std::make_shared<BraveAdventurerMovement>());
            enemy->setInput(std::make_shared<BasicAIInput>());
            enemy->setStats(std::make_shared<StatsComponent>(20));
            enemy->getStats()->setSpeed(.5);
            enemy->addScript(std::make_shared<MainCharScript>(false, sf::seconds(.5)));
            enemy->addScript(std::make_shared<KillScript>(false, 10, sf::seconds(.5)));
            enemy->setAudio(std::make_shared<AudioComponent>());
            enemy->setIdentification(std::make_shared<IDComponent>("","","enemy"));

            enemy->setPhysics(std::make_shared<SimpleBoxPhysics>(id,sf::Vector2f(34,42),0, PhysicsOptions::roundedCorners | PhysicsOptions::notRotatable | PhysicsOptions::sideSensors, enemy->getPosition()));

            ComponentManager::getInst().addEntity(id, enemy);
        }
    }
}
