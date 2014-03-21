#include "Components/Render/StaticSpriteComponent.h"
#include "Components/ComponentManager.h"

StaticSpriteComponent::~StaticSpriteComponent()
{
    //dtor
}

void StaticSpriteComponent::go(sf::Time) {
    auto posCom = ComponentManager::getInst().posSym.getComponent(getID());
    sprite.setOrigin(sprite.getTextureRect().width/2,sprite.getTextureRect().height/2);
    if(posCom!=NULL) {
        sf::Vector2f position = posCom->getPosition();
        sprite.setPosition(position);
        if(rendEng==NULL) {
            throw logic_error("Render engine not initialized yet");
        }
        else {
            rendEng->addSprite(&sprite);
        }
    }
    else { //No world position? // TODO (Thomas Luppi#1#03/16/14): Add checks for screen position, which requires changing the rendering code a bit
        rendEng->removeSprite(&sprite);
        cout << "No world position" << endl;
    }
}
