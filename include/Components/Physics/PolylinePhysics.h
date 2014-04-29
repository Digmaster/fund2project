#ifndef POLYLINEPHYSICS_H
#define POLYLINEPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"
#include <vector>
#include <SFML/Graphics.hpp>

///Creates a series of physics lines (rope)
class PolylinePhysics : public PhysicsComponent
{
    public:
        PolylinePhysics() : PhysicsComponent() {}
        ///takes a series of xy coordinates
        PolylinePhysics(unsigned int, std::vector<sf::Vector2i>);
        virtual ~PolylinePhysics();

        void go(sf::Time);
    protected:
    private:
        b2BodyDef physBodyDef;
        //b2PolygonShape boundaryShape;
        b2ChainShape polylineChain;
        b2FixtureDef boundaryFixtureDef;
        //int screenHeight; //Need to convert Box2d to SFML coordinates
};

#endif // POLYLINEPHYSICS_H
