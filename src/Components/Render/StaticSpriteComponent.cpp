#include "Components/Render/StaticSpriteComponent.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"
#include "Components/Entity.h"
#include "Components/Positional/WorldPositionComponent.h"

#include <stdexcept>

using namespace std;
using namespace sf;

StaticSpriteComponent::~StaticSpriteComponent()
{
    //dtor
}

StaticSpriteComponent::StaticSpriteComponent(string texture, const IntRect &rectangle) : RenderComponent() {
    sprite.setTexture(*texMan.getTexture(texture));
    sprite.setTextureRect(rectangle);
    // NOTE (Thomas Luppi#1#03/21/14): Check if the texturemanager actually works here
}

void StaticSpriteComponent::go(sf::Time, Entity* entity) {
    auto posCom = entity->getPosition();
    sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
    if(posCom!=NULL) {
        sf::Vector2f position = posCom->getPosition();
        float angle = posCom->getRotation();
        sprite.setPosition(position);
        sprite.setRotation(-angle*57.2957795);
        if(rendEng==NULL) {
            throw logic_error("Render engine not initialized yet");
        }
        else {
            rendEng->addSprite(&sprite, posCom->getLayer());
        }
    }
    else { //No world position? // TODO (Thomas Luppi#1#03/16/14): Add checks for screen position, which requires changing the rendering code a bit
    }
}

sf::Drawable* StaticSpriteComponent::getDrawable() {
    return &sprite;
}
