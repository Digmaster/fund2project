#include "TextComponent.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"
#include "Components/Entity.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Rendering/FontManager.h"

#include <stdexcept>

TextComponent::TextComponent(std::string text, int fontSize, sf::Color color, int fontStyle, sf::Font* font)
{
    textDrawable.setString(text);
    textDrawable.setCharacterSize(fontSize);
    textDrawable.setStyle(fontStyle);
    textDrawable.setColor(color);
    if(font==nullptr)
    {
        font = FontManager::getFont("assets/RPM Bold.otf");
    }
    textDrawable.setFont(*font);
}

TextComponent::~TextComponent()
{
    //dtor
}

void TextComponent::go(sf::Time, Entity* entity) {
    auto posCom = entity->getPosition();
    textDrawable.setOrigin(textDrawable.getLocalBounds().width/2,textDrawable.getLocalBounds().height/2);
    if(posCom!=NULL) {
        sf::Vector2f position = posCom->getPosition();
        float angle = posCom->getRotation();
        textDrawable.setPosition(position);
        textDrawable.setRotation(-angle*57.2957795);
        if(rendEng==NULL) {
            throw std::logic_error("Render engine not initialized yet");
        }
        else {
            rendEng->addSprite(&textDrawable, posCom->getLayer());
        }
    }
    else { //No world position? // TODO (Thomas Luppi#1#03/16/14): Add checks for screen position, which requires changing the rendering code a bit
    }
}
