#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/ComponentManager.h"

SimpleBoxPhysics::SimpleBoxPhysics(unsigned int ID) : PhysicsComponent(ID), physBody()
{
    physBodyDef.type = b2_dynamicBody;
    physBodyDef.position.Set(10,10);
    physBodyDef.angle = 0;
    physBody = _world->CreateBody(&physBodyDef);
    boxShape.SetAsBox(1,1);
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    physBody->CreateFixture(&boxFixtureDef);
    screenHeight = atoi(Options::instance().get("screen_height").c_str());
}

SimpleBoxPhysics::~SimpleBoxPhysics()
{
    //dtor
}

void SimpleBoxPhysics::go(sf::Time frameTime) {
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    //The body is the one that contains the position, velocity, etc. not the body definition
    position->setPosition(sf::Vector2f(physBody->GetPosition().x, screenHeight-physBody->GetPosition().y));
    cout << physBodyDef.position.x << " " << physBodyDef.position.y << " " << physBodyDef.awake << endl;
}
