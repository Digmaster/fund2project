#include "Components/ComponentManager.h"
ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 1;
    return ID++;
}

void ComponentManager::processAll(sf::Time frameTime) {
    physSym.process(frameTime);
//    cout << "Position" << endl;
    posSym.process(frameTime);
//    cout << "Input" << endl;
    idSym.process(frameTime);

    inputSym.process(frameTime);
//    cout << "Movement" << endl;
    moveSym.process(frameTime);
//    cout << "Etcetera" << endl;
    etcSym.process(frameTime);
//    cout << "Rendering" << endl;
    targetSym.process(frameTime);
    scriptSym.process(frameTime);
    rendSym.process(frameTime);
}

unsigned int ComponentManager::name2ID(std::string name) {
    for(typename std::map<unsigned int, IDComponent*>::iterator it = idSym.components.begin(); it!=idSym.components.end(); it++) {
        if(it->second->getName()==name)
            return it->first;
    }
    return 0;
}
