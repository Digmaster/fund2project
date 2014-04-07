#ifndef POLYGONPHYSICS_H
#define POLYGONPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"
#include <vector>
#include <SFML/Graphics.hpp>

class PolygonPhysics : public PhysicsComponent
{
    public:
        PolygonPhysics() : PhysicsComponent() {}
        PolygonPhysics(unsigned int, std::vector<sf::Vector2i>);
        virtual ~PolygonPhysics();

        void go(sf::Time);
    protected:
    private:
        b2BodyDef physBodyDef;
        b2PolygonShape boundaryShape;
        b2FixtureDef boundaryFixtureDef;
        //int screenHeight; //Need to convert Box2d to SFML coordinates
};


#endif // POLYGONPHYSICS_H
