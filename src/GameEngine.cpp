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
#include <SFML/Audio.hpp>

//Default constructor: creates engines the game is dependent on to run
GameEngine::GameEngine(){
    rendEng = new RenderEngine;
    physEng = new PhysicsEngine;
    inputEng = new InputEngine;
    paused = false;
    died = false;
    ComponentBase::setEngine(this);
}

GameEngine::~GameEngine()
{
    //dtor
}

//Loop through the game
void GameEngine::go() {
    init();
    gameLoop();
}

//initialize
void GameEngine::init() {
    //rendEng.init();
    physEng->setDebugDraw(rendEng->window);
}

//Main loop that the game goes though
void GameEngine::gameLoop() {
    sf::Clock frameClock;

    SpriteManager spriteMan;
    //spriteMan.loadFile("assets/testSprite.xml");
    spriteMan.loadFile("assets/SamusSprites.xml");
    //spriteMan.loadSpriteFile("assets/art/testSpriteSheet.sprites");

    Level testLevel;
    testLevel.loadLevel("longtest.tmx", rendEng);

    //play background music
    sf::Music music; //Declare music object
    music.openFromFile("assets/sound/stormeaglegenesis.wav"); //open this sound for music
    music.setVolume(30); //Set volume of music
    music.setLoop(true); //loop the music throughout
    music.play(); //sound should now play throughout the game!

    while (rendEng->window.isOpen() && !died) {
        sf::Time frameTime = frameClock.restart();
        ComponentManager::getInst().physSym.process(frameTime);
        ComponentManager::getInst().posSym.process(frameTime);
        ComponentManager::getInst().idSym.process(frameTime);
        ComponentManager::getInst().inputSym.process(frameTime);
        ComponentManager::getInst().moveSym.process(frameTime);
        ComponentManager::getInst().etcSym.process(frameTime);
        ComponentManager::getInst().targetSym.process(frameTime);
        ComponentManager::getInst().scriptSym.process(frameTime);
        ComponentManager::getInst().rendSym.process(frameTime);
        ComponentManager::getInst().audioSym.process(frameTime);

        rendEng->render(frameTime, physEng);
        physEng->step(frameTime);
        inputEng->update(this);
    }
}
