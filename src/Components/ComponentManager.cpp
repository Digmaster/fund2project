#include "Components/ComponentManager.h"
ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 1;
    return ID++;
}

void ComponentManager::processAll(sf::Time frameTime) {
    posSym.process(frameTime);
    inputSym.process(frameTime);
    moveSym.process(frameTime);
    etcSym.process(frameTime);
    rendSym.process(frameTime);
}
