#include "ScriptComponent.h"
#include "Components/ComponentManager.h"

ScriptComponent::~ScriptComponent()
{
    //dtor
}

ScriptComponent::ScriptComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->scriptSym.addComponent(this);
    active = true;
}
