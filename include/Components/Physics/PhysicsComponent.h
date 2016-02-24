#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Components/ComponentBase.h"
#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

class PhysicsEngine;

///Simple physics components. Used for sensors, collision, etc
class PhysicsComponent : public ComponentBase
{
    public:
        PhysicsComponent();
        virtual ~PhysicsComponent();
        ///Returns true if the physics object is touching something on the bottom
        virtual bool onGround() {return false;}
        virtual unsigned int touchingGround() {return 0;}
        ///Returns true if the physics object is touching something on the letf
        virtual bool onLeft() {return false;}
        virtual unsigned int touchingLeft() {return 0;}
        ///Returns true if the physics object is touching something on the right
        virtual bool onRight() {return false;}
        virtual unsigned int touchingRight(){return 0;}
        ///Returns true if the physics object is touching something on the top
        virtual bool onTop() {return false;}
        virtual unsigned int touchingTop(){return 0;}
        ///Returns true if the physics object is touching something, somewhere
        virtual bool onBody() {return false;}
        virtual unsigned int touchingBody(){return 0;}
        ///Returns true if the physics body is over a sensor by the type "Ladder"
        virtual bool overLadder() { return false;}
        ///Returns the physics body. If there are multiple physics bodies, the most important one will be returned
        b2Body* getBody() {return physBody;}

        ///Get Polygon Path
        /** Used for path following **/
        virtual std::vector<b2Vec2> getPath() = 0;

        /// Returns if the path is closed (a circle) or open
        virtual bool isPathClosed() = 0;

    protected:
        static int pixelsPerMeter;
        b2Body* physBody;
    private:
};
///An enumeration used for flags to physics component creation
/** Not all flags are supported on all components **/
enum PhysicsOptions{
    sensor = 1, //Not solid
    notRotatable = 2, //Not rotatable
    roundedCorners = 4, //Rounds the corners somewhat
    isStatic = 8, //Doesn't allow it to move
    sideSensors = 16, //Adds side, top, and bottom sensors.
    isBullet = 32,
    isKinematic = 64
};

enum SensorSides {
    body = 0,
    top = 1,
    bottom = 2,
    left = 3,
    right = 4,
};

#endif // PHYSICSCOMPONENT_H
