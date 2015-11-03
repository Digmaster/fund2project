#include "Components/ComponentBase.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"
#include <iostream>

ComponentManager* ComponentBase::compMan = &ComponentManager::getInst();
RenderEngine* ComponentBase::rendEng = NULL;
GameEngine* ComponentBase::eng = NULL;

unsigned int ComponentBase::getNewID() {
    return ComponentManager::getNewID();
}
