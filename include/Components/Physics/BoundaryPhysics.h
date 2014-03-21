#ifndef BOUNDARYPHYSICS_H
#define BOUNDARYPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"

class BoundaryPhysics : public PhysicsComponent
{
    public:
        BoundaryPhysics() : PhysicsComponent() {}
        BoundaryPhysics(unsigned int, float, float, float, float);
        virtual ~BoundaryPhysics();

        void go(sf::Time);
    protected:
    private:
        b2BodyDef physBodyDef;
        b2EdgeShape boundaryShape;
        b2FixtureDef boundaryFixtureDef;
        //int screenHeight; //Need to convert Box2d to SFML coordinates
};


#endif // BOUNDARYPHYSICS_H
