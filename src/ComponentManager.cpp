#include "ComponentManager.h"
ComponentManager::~ComponentManager() {
    //dtor
}

unsigned int ComponentManager::getNewID() {
    static unsigned int ID = 0;
    return ID++;
}
