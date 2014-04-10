#include "Physics/PhysicsEngine.h"
#include "Components/Physics/PhysicsComponent.h"
#include <iostream>

using namespace std;

PhysicsEngine::PhysicsEngine()
{
    b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
    _world = new b2World(gravity);
    _velocityIterations = 8;
    _positionIterations = 3;
    _world->SetContactListener(&contactListeners);

}

PhysicsEngine::~PhysicsEngine()
{
    delete _world;
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

}

void ContactListener::BeginContact(b2Contact* contact) {
    //cout << (int)(contact->GetFixtureA()->GetUserData())/10 << " = " << (int)(contact->GetFixtureB()->GetUserData())/10 << endl;
    for(deque<b2ContactListener*>::iterator it = listenerList.begin(); it != listenerList.end(); it++)
        (*it)->BeginContact(contact);
}

void ContactListener::EndContact(b2Contact* contact) {
    for(deque<b2ContactListener*>::iterator it = listenerList.begin(); it != listenerList.end(); it++)
        (*it)->EndContact(contact);
}

void ContactListener::addListener(b2ContactListener* input) {
    listenerList.push_back(input);
}

void ContactListener::removeListener(b2ContactListener* input){
    deque<b2ContactListener*>::iterator it = find(listenerList.begin(), listenerList.end(), input);
    if(it!=listenerList.end())
        listenerList.erase(it);
}
