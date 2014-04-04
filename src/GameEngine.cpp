#include "GameEngine.h"

#include "Components/Render/AnimatedComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Movement/BraveAdventurerMovement.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Physics/BoundaryPhysics.h"
#include "Components/Render/StaticSpriteComponent.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Script/Camera.h"
#include "LevelLoader.h"
#include "Rendering/SpriteManager.h"
#include "Rendering/RenderEngine.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"
#include "InputEngine.h"


GameEngine::GameEngine(){
    rendEng = new RenderEngine;
    physEng = new PhysicsEngine;
    inputEng = new InputEngine;
    paused = false;
    ComponentBase::setEngine(this);
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
    physEng->setDebugDraw(rendEng->window);
}

void GameEngine::gameLoop() {
    sf::Clock frameClock;

    SpriteManager spriteMan;
    spriteMan.loadFile("assets/testSprite.xml");
    spriteMan.loadFile("assets/SamusSprites.xml");
    spriteMan.loadSpriteFile("assets/art/testSpriteSheet.sprites");

    ///THIS IS IMPORTANT!!!
    /// I changed it so that when you create a component it's automatically added to the right component system!!!!!
    /// yaaaaaaaaaaay

    Level testLevel;
    testLevel.loadLevel("longtest.tmx", rendEng);

    while (rendEng->window.isOpen()) {
        sf::Time frameTime = frameClock.restart();
        //cout << 1000/frameTime.asMilliseconds() << endl; //fps

        ComponentManager::getInst().processAll(frameTime);


        rendEng->render(frameTime, physEng);
        physEng->step(frameTime);
        inputEng->update(this);
    }
}
