#include "ScriptComponent.h"
#include "Components/ComponentManager.h"

ScriptComponent::~ScriptComponent()
{
    //dtor
}

ScriptComponent::ScriptComponent() : ComponentBase() {
    active = true;
}
