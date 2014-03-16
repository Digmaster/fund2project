#include "GameEngine.h"

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
    while (rendEng.window.isOpen()) {
        sf::Time frameTime = frameClock.restart();
        ComponentManager* comp = &ComponentManager::getInst();
        comp->rendSym.process(frameTime);
        //entList.update();
        //Input goes here
        //Any sort of physics stuff
        //Actor Updates go here
        rendEng.render(frameTime);
    }
}
