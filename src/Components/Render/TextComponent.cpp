#include "TextComponent.h"
#include "Components/ComponentManager.h"
#include "Rendering/RenderEngine.h"
#include "Components/Entity.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Rendering/FontManager.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Stats/StatsComponent.h"

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

TextComponent::TextComponent(uint32 thingToWatch, int fontSize, sf::Color color,int fontStyle, sf::Font* font)
{
    this->thingToWatch = thingToWatch;
    textDrawable.setString("ERROR");
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
    if(thingToWatch!=ThingsToWatch::nothing)
    {
        if(entity->getTarget()!=nullptr && entity->getTarget()->getTarget()!=0)
        {
            Entity* target = ComponentManager::getInst()[entity->getTarget()->getTarget()];
            if(target!=nullptr)
            {
                if(thingToWatch==ThingsToWatch::health)
                {
                    if(target->getStats()!=nullptr)
                    {
                        textDrawable.setString(patch::to_string(target->getStats()->getHealth()));
                    }
                }
            }
        }
    }

    auto posCom = entity->getPosition();
    textDrawable.setOrigin(textDrawable.getLocalBounds().width/2,textDrawable.getLocalBounds().height/2);
    if(posCom!=NULL) {
        sf::Vector2f position = posCom->getPosition();
        float angle = posCom->getRotation();
        position.x += textDrawable.getGlobalBounds().width/2;
        position.y += textDrawable.getGlobalBounds().height/2;
        textDrawable.setPosition(position);
        textDrawable.setRotation(-angle*57.2957795);
        if(rendEng==NULL) {
            throw std::logic_error("Render engine not initialized yet");
        }
        else {
            rendEng->addSprite(&textDrawable, posCom->getLayer());
        }
    }
}

Entity::listener& TextComponent::getHandler()
{
    using namespace std::placeholders;
    auto handler = std::bind(&TextComponent::HandleMessage, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::HEALTH_CHANGE, handler));
    return out.end()->second;
}

void TextComponent::HandleMessage(Events event, EventObj* message, Entity* entity)
{
    switch(event)
    {
    case Events::HEALTH_CHANGE:
        HealthChange* obj = (HealthChange*)message;
        textDrawable.setString(patch::to_string(obj->newHealth));

        break;
    }
}
