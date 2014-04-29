#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Components/ComponentBase.h"
#include <Box2D/Box2D.h>

class PhysicsEngine;

///Simple physics components. Used for sensors, collision, etc
class PhysicsComponent : public ComponentBase
{
    public:
        PhysicsComponent() : ComponentBase() {}
        PhysicsComponent(unsigned int ID);
        virtual ~PhysicsComponent();
        ///Returns true if the physics object is touching something on the bottom
        virtual bool onGround() {return false;}
        ///Returns true if the physics object is touching something on the letf
        virtual bool onLeft() {return false;}
        ///Returns true if the physics object is touching something on the right
        virtual bool onRight() {return false;}
        ///Returns true if the physics object is touching something on the top
        virtual bool onTop() {return false;}
        ///Returns true if the physics body is over a sensor by the type "Ladder"
        virtual bool overLadder() { return false;}
        ///Returns the physics body. If there are multiple physics bodies, the most important one will be returned
        b2Body* getBody() {return physBody;}
        //virtual b2PolygonShape* getShape() {return physBody->Get}
    protected:
        static int pixelsPerMeter;
        b2Body* physBody;
    private:
};
///An enumeration used for flags to physics component creation
/** Not all flags are supported on all components **/
enum PhysicsOptions{
    sensor = 0x01, //Not solid
    notRotatable = 0x02, //Not rotatable
    roundedCorners = 0x04, //Rounds the corners somewhat
    isStatic = 0x08, //Doesn't allow it to move
    sideSensors = 0x16 //Adds side, top, and bottom sensors.
};

#endif // PHYSICSCOMPONENT_H
