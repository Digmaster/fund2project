#include "SimpleBoxPhysics.h"
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
}

SimpleBoxPhysics::~SimpleBoxPhysics()
{
    //dtor
}

void SimpleBoxPhysics::go(sf::Time frameTime) {
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    position->setPosition(sf::Vector2f(physBodyDef.position.x,physBodyDef.position.y));
    cout << physBodyDef.position.x << " " << physBodyDef.position.y << " " << physBodyDef.awake << endl;
}
