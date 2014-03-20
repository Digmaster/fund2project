#ifndef SIMPLEBOXPHYSICS_H
#define SIMPLEBOXPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"


class SimpleBoxPhysics : public PhysicsComponent
{
    public:
        SimpleBoxPhysics() : PhysicsComponent() {}
        SimpleBoxPhysics(unsigned int ID);
        virtual ~SimpleBoxPhysics();

        void go(sf::Time);
    protected:
    private:
        b2BodyDef physBodyDef;
        b2Body* physBody;
        b2PolygonShape boxShape;
        b2FixtureDef boxFixtureDef;
};

#endif // SIMPLEBOXPHYSICS_H
