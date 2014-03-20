#include "GameEngine.h"

#include "Components/Render/AnimatedComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Rendering/SpriteManager.h"
#include "Components/Input/DumbKeyboardInputComponent.h"
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Input/BraveAdventurerInput.h"
#include "Components/Movement/BraveAdventurerMovement.h"
#include "SimpleBoxPhysics.h"

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

    unsigned int id = ComponentManager::getInst().getNewID();
    //AnimatedComponent testSprite(id);
    BraveAdventurerAnimatedComponent testSprite(id);
    testSprite.setSprite(spriteMan.getSprite("BraveAdventurer"));
    testSprite.sprite.setAnimation("WalkUp");

    WorldPositionComponent testPosition(id);
    testPosition.setPosition(sf::Vector2f(10,10));

    BraveAdventurerInput testInput(id);

    BraveAdventurerMovement testMovement(id);

    SimpleBoxPhysics testPhys(id);
    //DumbKeyboardInputComponent testInput(id);
    ComponentManager::getInst().physSym.addComponent(&testPhys);
    ComponentManager::getInst().inputSym.addComponent(&testInput);
    ComponentManager::getInst().posSym.addComponent(&testPosition);
    ComponentManager::getInst().rendSym.addComponent(&testSprite);
    ComponentManager::getInst().moveSym.addComponent(&testMovement);

    while (rendEng.window.isOpen()) {
        sf::Time frameTime = frameClock.restart();
        ComponentManager::getInst().processAll(frameTime);


        //entList.update();
        //Input goes here
        //Any sort of physics stuff
        //Actor Updates go here
        rendEng.render(frameTime);
        physEng.step(frameTime);
    }
}
