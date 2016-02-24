#ifndef POLYLINEPHYSICS_H
#define POLYLINEPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"
#include <vector>
#include <SFML/Graphics.hpp>

class WorldPositionComponent;

///Creates a series of physics lines (rope)
class PolylinePhysics : public PhysicsComponent
{
    public:
        ///takes a series of xy coordinates
        PolylinePhysics(unsigned int, std::vector<sf::Vector2i>, uint32 opts, std::shared_ptr<WorldPositionComponent> position);
        virtual ~PolylinePhysics();

        void go(sf::Time, Entity* entity);

        std::vector<b2Vec2> getPath();
        virtual bool isPathClosed() {return false;}
    protected:
    private:
        b2BodyDef physBodyDef;
        //b2PolygonShape boundaryShape;
        b2ChainShape polylineChain;
        b2FixtureDef boundaryFixtureDef;
        //int screenHeight; //Need to convert Box2d to SFML coordinates
};

#endif // POLYLINEPHYSICS_H
