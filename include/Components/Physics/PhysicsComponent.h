#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Components/ComponentBase.h"
#include <Box2D/Box2D.h>


class PhysicsComponent : public ComponentBase
{
    public:
        PhysicsComponent() : ComponentBase() {}
        PhysicsComponent(unsigned int ID);
        virtual ~PhysicsComponent();
        static void setWorld(b2World* world) {_world=world;}
        virtual bool onGround() {return false;}
        b2Body* getBody() {return physBody;}
    protected:
        static int pixelsPerMeter;
        static b2World* _world;
        b2Body* physBody;
    private:
};

#endif // PHYSICSCOMPONENT_H
