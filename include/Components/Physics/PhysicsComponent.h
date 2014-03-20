#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Components/ComponentBase.h"
#include <Box2D/Box2D.h>


class PhysicsComponent : public ComponentBase
{
    public:
        PhysicsComponent() : ComponentBase() {}
        PhysicsComponent(unsigned int ID) : ComponentBase(ID) {}
        virtual ~PhysicsComponent();
        static void setWorld(b2World* world) {_world=world;}
        bool onGround() {return false;}
    protected:
            static b2World* _world;
    private:
};

#endif // PHYSICSCOMPONENT_H
