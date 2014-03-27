#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <SFML/System/Time.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Components/Render/DebugDraw.h"
#include <deque>

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void addListener(b2ContactListener*);
    void removeListener(b2ContactListener*);
private:
    std::deque< b2ContactListener* > listenerList;
};

class PhysicsEngine
{
    public:
        PhysicsEngine();
        virtual ~PhysicsEngine();
        void step(sf::Time);
        void debugDraw();
        void setDebugDraw(sf::RenderWindow&);
        void init();
        ContactListener contactListeners;
        b2World* _world;
    protected:
    private:
        int _velocityIterations;
        int _positionIterations;
};

#endif // PHYSICSENGINE_H
