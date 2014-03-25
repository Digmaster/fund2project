#include "Components/ComponentBase.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"
#include <iostream>

ComponentManager* ComponentBase::compMan = &ComponentManager::getInst();
RenderEngine* ComponentBase::rendEng = NULL;

std::string ComponentBase::getMessage() {
    std::string output;

    if(messages.size() > 0) {
        output = messages.front();
        messages.pop_front();
    }
    else
        output = "NOMESSAGE";
    return output;
}

unsigned int ComponentBase::getNewID() {
    return ComponentManager::getNewID();
}
