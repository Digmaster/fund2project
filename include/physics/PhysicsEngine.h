#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>


class PhysicsEngine
{
    public:
        PhysicsEngine();
        virtual ~PhysicsEngine();
        void step(sf::Time);
        void init();
    protected:
    private:
        b2World* _world;
        int _velocityIterations;
        int _positionIterations;
};

#endif // PHYSICSENGINE_H
