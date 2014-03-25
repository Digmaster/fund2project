#ifndef SIMPLEBOXPHYSICS_H
#define SIMPLEBOXPHYSICS_H

#include "Components\Physics\PhysicsComponent.h"


class SimpleBoxPhysics : public PhysicsComponent
{
    public:
        SimpleBoxPhysics() : PhysicsComponent() {}
        SimpleBoxPhysics(unsigned int, int x = 32, int y = 32, bool isStatic = false, bool rotatable = true, bool roundedCorners = false, bool isSensor = false);
        virtual ~SimpleBoxPhysics();
        void setRotatable(bool);
        void go(sf::Time);
    protected:
    private:
        b2BodyDef physBodyDef;
        b2PolygonShape boxShape;
        b2FixtureDef boxFixtureDef;
        int screenHeight; //Need to convert Box2d to SFML coordinates
};

#endif // SIMPLEBOXPHYSICS_H
