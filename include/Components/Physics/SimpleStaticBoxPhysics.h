#ifndef SIMPLEBOXPHYSICS_H
#define SIMPLEBOXPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"
#include "Options.h"


class SimpleStaticBoxPhysics : public PhysicsComponent
{
    public:
        SimpleStaticBoxPhysics() : PhysicsComponent() {}
        SimpleStaticBoxPhysics(unsigned int, int x = 32, int y = 32);
        virtual ~SimpleStaticBoxPhysics();
        void go(sf::Time);
    protected:
    private:
        b2BodyDef physBodyDef;
        b2PolygonShape boxShape;
        b2FixtureDef boxFixtureDef;
        int screenHeight; //Need to convert Box2d to SFML coordinates
};

#endif // SIMPLEBOXPHYSICS_H
