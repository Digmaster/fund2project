#include "GameEngine.h"

#include "Components/Render/AnimatedComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Rendering/SpriteManager.h"
#include "Components/Input/DumbKeyboardInputComponent.h"
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Input/BraveAdventurerInput.h"
#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Physics/BoundaryPhysics.h"
#include "Components/Render/StaticSpriteComponent.h"


GameEngine::GameEngine()
    : rendEng() {
}

GameEngine::~GameEngine()
{
    //dtor
}

void GameEngine::go() {
    init();
    gameLoop();
}

void GameEngine::init() {
    //rendEng.init();
}

void GameEngine::gameLoop() {
    sf::Clock frameClock;

    SpriteManager spriteMan;
    spriteMan.loadFile("assets/testSprite.xml");
    spriteMan.loadFile("assets/SamusSprites.xml");

    sf::IntRect rec(0, 0, 32, 32);


    unsigned int id2 = ComponentManager::getInst().getNewID();
    StaticSpriteComponent testSprite2("assets/art/box.png", rec, id2);

     WorldPositionComponent testPosition2(id2);
    testPosition2.setPosition(sf::Vector2f(40,40));

    SimpleBoxPhysics testPhys2(id2, 40, 40);

    unsigned int id = ComponentManager::getInst().getNewID();
    //AnimatedComponent testSprite(id);
    BraveAdventurerAnimatedComponent testSprite(id);
    testSprite.setSprite(spriteMan.getSprite("BraveAdventurer"));
    testSprite.sprite.setAnimation("WalkUp");

    WorldPositionComponent testPosition(id);
    testPosition.setPosition(sf::Vector2f(100,10));

    BraveAdventurerInput testInput(id);

    BraveAdventurerMovement testMovement(id);

    SimpleBoxPhysics testPhys(id);



    //DumbKeyboardInputComponent testInput(id);
    ComponentManager::getInst().physSym.addComponent(&testPhys);
    ComponentManager::getInst().inputSym.addComponent(&testInput);
    ComponentManager::getInst().posSym.addComponent(&testPosition);

    ComponentManager::getInst().rendSym.addComponent(&testSprite);

    ComponentManager::getInst().moveSym.addComponent(&testMovement);

    ComponentManager::getInst().posSym.addComponent(&testPosition2);
    ComponentManager::getInst().rendSym.addComponent(&testSprite2);
    ComponentManager::getInst().physSym.addComponent(&testPhys2);

    id = ComponentManager::getInst().getNewID();

    BoundaryPhysics floor(id, 0.0f, 400.0f, 900.0f, 400.0f);

    WorldPositionComponent floorPosition(id);
    //floorPosition.setPosition(sf::Vector2f(0,0));

    ComponentManager::getInst().physSym.addComponent(&floor);
     ComponentManager::getInst().posSym.addComponent(&floorPosition);

    physEng.setDebugDraw(rendEng.window);

    while (rendEng.window.isOpen()) {
        sf::Time frameTime = frameClock.restart();
        ComponentManager::getInst().processAll(frameTime);


        //entList.update();
        //Input goes here
        //Any sort of physics stuff
        //Actor Updates go here
        rendEng.render(frameTime);
        physEng.step(frameTime);
        physEng.debugDraw();
    }
}
