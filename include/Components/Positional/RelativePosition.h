#ifndef RELATIVEPOSITION_H
#define RELATIVEPOSITION_H

#include <WorldPositionComponent.h>
#include <SFML/System/Vector2.hpp>
#include <Box2D/Box2D.h>

class RelativePosition : public WorldPositionComponent
{
    public:
        RelativePosition(sf::Vector2f position, unsigned int relativeToID, uint32 relativeTo, int Layer, float Rotation);

        virtual void go(sf::Time frameTime, Entity* entity);

        virtual sf::Vector2f getPosition() {
            return modifiedPosition;}

        enum RelativePositionLocation
        {
            TopLeft,
            TopRight,
            BottomLeft,
            BottomRight
        };
    protected:
    private:
        sf::Vector2f modifiedPosition;
        int relativeToID;
        uint32 relativeTo;
};

#endif // RELATIVEPOSITION_H
