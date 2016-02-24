#ifndef BOUNDARYPHYSICS_H
#define BOUNDARYPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"

///Creates lines of physics-ness. only two points though
class BoundaryPhysics : public PhysicsComponent
{
    public:
        BoundaryPhysics(int, float, float, float, float, uint32 opts = 0);
        virtual ~BoundaryPhysics();

        void go(sf::Time, Entity* entity);

        std::vector<b2Vec2> getPath();
        virtual bool isPathClosed() {return false;}
    protected:
    private:
        b2BodyDef physBodyDef;
        b2EdgeShape boundaryShape;
        b2FixtureDef boundaryFixtureDef;
        //int screenHeight; //Need to convert Box2d to SFML coordinates
};


#endif // BOUNDARYPHYSICS_H
