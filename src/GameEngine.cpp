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
    //spriteMan.loadSpriteFile("assets/art/testSpriteSheet.sprites");y

    Level testLevel;
    testLevel.loadLevel("longtest.tmx", rendEng);

    while (rendEng->window.isOpen()) {
        sf::Time frameTime = frameClock.restart();
        //cout << 1000/frameTime.asMilliseconds() << endl; //fps

        //ComponentManager::getInst().processAll(frameTime);
        //cout << "---------------------------------------------------" << endl;
        ComponentManager::getInst().physSym.process(frameTime);
        //cout << "Physics " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().posSym.process(frameTime);
        //cout << "Position "  << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().idSym.process(frameTime);
        //cout << "ID " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().inputSym.process(frameTime);
        //cout << "Input " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().moveSym.process(frameTime);
        //cout << "Movement " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().etcSym.process(frameTime);
        //cout << "Etcetera " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().targetSym.process(frameTime);
        //cout << "Target " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().scriptSym.process(frameTime);
        //cout << "scripts " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();
        ComponentManager::getInst().rendSym.process(frameTime);
        //cout << "Rendering " << frameClock.getElapsedTime().asMicroseconds() << endl;
        //frameClock.restart();


        rendEng->render(frameTime, physEng);
        physEng->step(frameTime);
        inputEng->update(this);
        //cout << "ENgs " << frameClock.getElapsedTime().asMicroseconds() << endl;
    }
}
