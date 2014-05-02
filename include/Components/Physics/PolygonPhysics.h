#ifndef POLYGONPHYSICS_H
#define POLYGONPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"
#include <vector>
#include <SFML/Graphics.hpp>

class FootContactListener;

///Creates a physics polygon from a set of points
class PolygonPhysics : public PhysicsComponent
{
    public:
        PolygonPhysics() : PhysicsComponent() {}
        ///X-Y Points! Last line is automatically connected to the last to create the polygon.
        PolygonPhysics(unsigned int, std::vector<sf::Vector2i>);
        virtual ~PolygonPhysics();

        void go(sf::Time);

        bool onTop();
        unsigned int touchingTop();

    protected:
    private:
        FootContactListener* headListener;
        b2BodyDef physBodyDef;
        b2PolygonShape boundaryShape;
        b2FixtureDef boundaryFixtureDef;
        //int screenHeight; //Need to convert Box2d to SFML coordinates
};


#endif // POLYGONPHYSICS_H
