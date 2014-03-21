#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/ComponentManager.h"

SimpleBoxPhysics::SimpleBoxPhysics(unsigned int ID, int x, int y) : PhysicsComponent(ID)
{
    physBodyDef.type = b2_dynamicBody;
    physBodyDef.position.Set(0,0);
    physBodyDef.angle = 0;
    physBody = _world->CreateBody(&physBodyDef);
    boxShape.SetAsBox(x/pixelsPerMeter,y/pixelsPerMeter);
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
    //screenHeight
    //Times 32, as 32 pixels is ~one meter
    position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)));
    //cout << physBody->GetPosition().x << " " << physBody->GetPosition().y << " " << physBodyDef.awake << endl;
}
