#include "Physics/PhysicsEngine.h"
#include "Components/Physics/PhysicsComponent.h"
#include <iostream>

PhysicsEngine::PhysicsEngine()
{
    b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
    _world = new b2World(gravity);
    _velocityIterations = 8;
    _positionIterations = 3;
    PhysicsComponent::setWorld(_world);
}

PhysicsEngine::~PhysicsEngine()
{
    //dtor
}

void PhysicsEngine::step(sf::Time frameTime)
{
    float updatetime = frameTime.asMicroseconds()/1000000.0f;
    _world->Step(updatetime, _velocityIterations, _positionIterations);
}

void PhysicsEngine::init()
{
    delete _world;
}
