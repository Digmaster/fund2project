#include "GameEngine.h"

#include "Components/Render/AnimatedComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Input/BraveAdventurerInput.h"
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


GameEngine::GameEngine(){
    rendEng = new RenderEngine;
    physEng = new PhysicsEngine;
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

/*<<<<<<< .mine
    sf::IntRect rec(0, 0, 70, 100);
=======
>>>>>>> .r34

    //Create Shaq
<<<<<<< .mine
    unsigned int id2 = ComponentManager::getInst().getNewID();
    StaticSpriteComponent testSprite2("assets/art/shaq.png", rec, id2);

    WorldPositionComponent testPosition2(id2);
    testPosition2.setPosition(sf::Vector2f(200,100));
    testPosition2.setLayer(5);

    SimpleBoxPhysics testPhys2(id2, 70, 100, true, false);
    //wtestPhys2.setRotatable(false);

    //Create Brave Adventurer
    unsigned int id = ComponentManager::getInst().getNewID();
    //AnimatedComponent testSprite(id);
    BraveAdventurerAnimatedComponent testSprite(id);
    testSprite.setSprite(spriteMan.getSprite("BraveAdventurer"));
    testSprite.sprite.setAnimation("WalkUp");

    WorldPositionComponent testPosition(id);
    testPosition.setPosition(sf::Vector2f(100,10));
    testPosition.setLayer(5);

    BraveAdventurerInput testInput(id);

    BraveAdventurerMovement testMovement(id);

    SimpleBoxPhysics testPhys(id,32,32,false,false);
    testPhys.setRotatable(false);



=======
>>>>>>> .r34*/
    ///THIS IS IMPORTANT!!!
    /// I changed it so that when you create a component it's automatically added to the right component system!!!!!
    /// yaaaaaaaaaaay


    //DumbKeyboardInputComponent testInput(id);

  /*  id = ComponentManager::getInst().getNewID();

    BoundaryPhysics floor(id, 0.0f, 400.0f, 900.0f, 400.0f);

    WorldPositionComponent floorPosition(id);
    floorPosition.setPosition(sf::Vector2f(0,0)); */
    Level testLevel;
    testLevel.loadLevel("longtest.tmx", rendEng);
    /*unsigned int id3 = ComponentManager::getInst().getNewID();
    Camera testCamera(id3, testLevel.width, testLevel.height);
    TargetComponent testTarget(id3, id);
    */

/*<<<<<<< .mine
    while (rendEng.window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
=======
*/
    while (rendEng->window.isOpen()) {
//>>>>>>> .r34
        sf::Time frameTime = frameClock.restart();
        ComponentManager::getInst().processAll(frameTime);


        //entList.update();
        //Input goes here
        //Any sort of physics stuff
        //Actor Updates go here
        rendEng->render(frameTime, physEng);
        physEng->step(frameTime);
        sf::Event event;
        while (rendEng->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rendEng->window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                rendEng->window.close();
            if (event.type == sf::Event::Resized)
                rendEng->view.setSize(event.size.width, event.size.height);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
                rendEng->toggleDebug();
        }
    }
}
