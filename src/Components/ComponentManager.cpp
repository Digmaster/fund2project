#include "Components/ComponentManager.h"
ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 1;
    return ID++;
}

void ComponentManager::processAll(sf::Time frameTime) {
    cout << "Position" << endl;
    posSym.process(frameTime);
    cout << "Input" << endl;
    inputSym.process(frameTime);
    cout << "Movement" << endl;
    moveSym.process(frameTime);
    cout << "Etcetera" << endl;
    etcSym.process(frameTime);
    cout << "Rendering" << endl;
    rendSym.process(frameTime);
}
