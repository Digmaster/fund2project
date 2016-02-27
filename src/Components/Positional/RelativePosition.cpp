#include "RelativePosition.h"
#include "Components/ComponentManager.h"

RelativePosition::RelativePosition(sf::Vector2f position, unsigned int relativeToID, uint32 relativeTo, int Layer, float Rotation) : WorldPositionComponent(position, Layer, Rotation)
{
    this->relativeToID=relativeToID;
    this->relativeTo=relativeTo;
}

void RelativePosition::go(sf::Time frameTime, Entity* entity)
{
    Entity* to = ComponentManager::getInst()[relativeTo];
    if(to!=nullptr && to->getPosition()!=nullptr)
    {
        modifiedPosition.x = position.x + to->getPosition()->getPosition().x;
        modifiedPosition.y = position.y + to->getPosition()->getPosition().y;
    }
}
