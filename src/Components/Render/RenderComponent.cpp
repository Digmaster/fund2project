#include "Components/Render/RenderComponent.h"
#include "Components/ComponentManager.h"

RenderComponent::RenderComponent() : ComponentBase() {
}

TextureManager RenderComponent::texMan;

RenderComponent::~RenderComponent()
{
}
