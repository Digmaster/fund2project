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
        static void setEngine(PhysicsEngine* input) {physEng=input;}
        virtual bool onGround() {return false;}
        virtual bool onLeft() {return false;}
        virtual bool onRight() {return false;}
        virtual bool onTop() {return false;}
        b2Body* getBody() {return physBody;}
    protected:
        static int pixelsPerMeter;
        static PhysicsEngine* physEng;
        b2Body* physBody;
    private:
};

#endif // PHYSICSCOMPONENT_H
