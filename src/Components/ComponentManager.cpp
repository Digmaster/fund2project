#include "Components/ComponentManager.h"
ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 1;
    return ID++;
}

void ComponentManager::processAll(sf::Time frameTime) {
    //cout << "Physics" << endl;
    physSym.process(frameTime);
    //cout << "Position" << endl;
    posSym.process(frameTime);
    //cout << "Input" << endl;
    idSym.process(frameTime);
    //cout << "Input" << endl;
    inputSym.process(frameTime);
    //cout << "Movement" << endl;
    moveSym.process(frameTime);
    //cout << "Etcetera" << endl;
    etcSym.process(frameTime);
    //cout << "Target" << endl;
    targetSym.process(frameTime);
    //cout << "scripts" << endl;
    scriptSym.process(frameTime);
    //cout << "Rendering" << endl;
    rendSym.process(frameTime);
    audioSym.process(frameTime);
}

unsigned int ComponentManager::name2ID(std::string name) {
    for(typename std::map<unsigned int, IDComponent*>::iterator it = idSym.components.begin(); it!=idSym.components.end(); it++) {
        if(it->second->getName()==name)
            return it->first;
    }
    return 0;
}
