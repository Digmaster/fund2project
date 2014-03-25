#include "Components/Render/RenderComponent.h"
#include "Components/ComponentManager.h"

RenderComponent::RenderComponent() : ComponentBase() {
}

RenderComponent::RenderComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->rendSym.addComponent(this);
}

TextureManager RenderComponent::texMan;

RenderComponent::~RenderComponent()
{
}
