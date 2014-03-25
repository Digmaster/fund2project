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

void PhysicsEngine::debugDraw(){
    _world->DrawDebugData();
}

void PhysicsEngine::setDebugDraw(sf::RenderWindow& window){
    // Create a new instance of our DebugDraw class
    DebugDraw* debugdraw = new DebugDraw(window);

    //Set the needed flags for the DebugDraw class
    uint32 flags = b2Draw::e_shapeBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    flags += b2Draw::e_jointBit;
    //flags += b2Draw::e_aabbBit;
    debugdraw->SetFlags(flags);

    //Set the physics worlds to use our DebugDraw class instead of the default one
    _world->SetDebugDraw( debugdraw );
}

void PhysicsEngine::init()
{
    delete _world;
}
