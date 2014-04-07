#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Components/ComponentBase.h"
#include <Box2D/Box2D.h>

class PhysicsEngine;

class PhysicsComponent : public ComponentBase
{
    public:
        PhysicsComponent() : ComponentBase() {}
        PhysicsComponent(unsigned int ID);
        virtual ~PhysicsComponent();
        virtual bool onGround() {return false;}
        virtual bool onLeft() {return false;}
        virtual bool onRight() {return false;}
        virtual bool onTop() {return false;}
        virtual bool overLadder() { return false;}
        b2Body* getBody() {return physBody;}
        //virtual b2PolygonShape* getShape() {return physBody->Get}
    protected:
        static int pixelsPerMeter;
        b2Body* physBody;
    private:
};

namespace PO {
    enum PhysicsOptions {
        sensor = 0x01,
        notRotatable = 0x02,
        roundedCorners = 0x04,
        isStatic = 0x08,
        sideSensors = 0x16
    };
}

#endif // PHYSICSCOMPONENT_H