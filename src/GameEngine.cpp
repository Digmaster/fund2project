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
#include "LevelLoader.h"


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
    physEng.setDebugDraw(rendEng.window);
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
    testPosition2.setPosition(sf::Vector2f(200,100));

    SimpleBoxPhysics testPhys2(id2, 32, 32);

    unsigned int id = ComponentManager::getInst().getNewID();
    //AnimatedComponent testSprite(id);
    BraveAdventurerAnimatedComponent testSprite(id);
    testSprite.setSprite(spriteMan.getSprite("BraveAdventurer"));
    testSprite.sprite.setAnimation("WalkUp");

    WorldPositionComponent testPosition(id);
    testPosition.setPosition(sf::Vector2f(100,10));

    BraveAdventurerInput testInput(id);

    BraveAdventurerMovement testMovement(id);

    SimpleBoxPhysics testPhys(id,32,32);
    testPhys.setRotatable(false);


    ///THIS IS IMPORTANT!!!
    /// I changed it so that when you create a component it's automatically added to the right component system!!!!!
    /// yaaaaaaaaaaay


    //DumbKeyboardInputComponent testInput(id);

    id = ComponentManager::getInst().getNewID();

    BoundaryPhysics floor(id, 0.0f, 400.0f, 900.0f, 400.0f);

    WorldPositionComponent floorPosition(id);
    //floorPosition.setPosition(sf::Vector2f(0,0));

    Level testLevel;
    testLevel.loadLevel("test.tmx");


    while (rendEng.window.isOpen()) {
        sf::Time frameTime = frameClock.restart();
        ComponentManager::getInst().processAll(frameTime);


        //entList.update();
        //Input goes here
        //Any sort of physics stuff
        //Actor Updates go here
        rendEng.render(frameTime, &physEng);
        physEng.step(frameTime);
    }
}
