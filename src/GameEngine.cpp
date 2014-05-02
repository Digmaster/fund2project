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
    //Load title screen
    sf::Texture title;
    title.loadFromFile("assets/art/titlescreen.png");
    sf::Sprite sprite1;
    sprite1.setTexture(title);

    sf::View titlescreen;
    titlescreen.setSize(rendEng->window.getSize().x, rendEng->window.getSize().y);
    titlescreen.setCenter(500,238);

    //Display title screen
    rendEng->window.setView(titlescreen);
    rendEng->centerViews(sf::Vector2f(-titlescreen.getSize().x/2,0));
    rendEng->window.draw(sprite1);
    rendEng->window.display();

    //Wait for user to press space
    while(!inputEng->getJump()){
        inputEng->update(this);
    }
    sf::Clock frameClock;

    SpriteManager spriteMan;
    spriteMan.loadFile("assets/SamusSprites.xml");

    Level testLevel;
    testLevel.loadLevel("longtest.tmx", rendEng);

    //play background music
    sf::Music music; //Declare music object
    music.openFromFile("assets/sound/stormeaglegenesis.wav"); //open this sound for music
    music.setVolume(30); //Set volume of music
    music.setLoop(true); //loop the music throughout
    music.play(); //sound should now play throughout the game!

    //Load dying sound
    sf::Sound dyingsound;
    sf::SoundBuffer dyingbuffer;
    dyingbuffer.loadFromFile("assets/sound/death.wav");
    dyingsound.setBuffer(dyingbuffer);
    dyingsound.setLoop(false);

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

        //Play dying sound
        if(playerDying){
            if(dyingsound.getStatus()!=sf::SoundSource::Status::Playing)
                dyingsound.play();
            music.stop();
        }
    }
    //Game over screen
    music.stop();
    sf::Texture gameover;
    gameover.loadFromFile("assets/art/gameover.png");
    sf::Sprite sprite;
    sprite.setTexture(gameover);

    //Display game over screen
    sf::View endView;
    endView.setSize(rendEng->window.getSize().x, rendEng->window.getSize().y);
    endView.setCenter(500,238);
    rendEng->window.setView(endView);
    //sprite.setPosition(gameover.getSize().x/2, gameover.getSize().y/2);
    rendEng->centerViews(sf::Vector2f(-gameover.getSize().x/2,0));
    rendEng->window.draw(sprite);
    rendEng->window.display();
    //Exit after 3 seconds
    sf::Clock clk;
    while(clk.getElapsedTime() <= sf::seconds(3)){
    }
}
