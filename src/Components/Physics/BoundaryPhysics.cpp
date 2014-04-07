#include "Components/Physics/BoundaryPhysics.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"
#include "GameEngine.h"

BoundaryPhysics::BoundaryPhysics(unsigned int ID, float x, float y, float endx, float endy) : PhysicsComponent(ID)
{
    physBodyDef.type = b2_staticBody;
    physBody = eng->physEng->_world->CreateBody(&physBodyDef);

    b2Vec2 floorvec[2];
    floorvec[0].Set( x/pixelsPerMeter, -y/pixelsPerMeter );
    floorvec[1].Set( endx/pixelsPerMeter, -endy/pixelsPerMeter );


    boundaryShape.Set(floorvec[0],floorvec[1]);
    boundaryFixtureDef.shape = &boundaryShape;
    boundaryFixtureDef.friction = 10;
    b2Fixture* fixture = physBody->CreateFixture(&boundaryFixtureDef);
    fixture->SetUserData( (void*)(getID()*10+2) );
    //screenHeight = atoi(Options::instance().get("screen_height").c_str());
}

BoundaryPhysics::~BoundaryPhysics()
{
    //dtor
}

void BoundaryPhysics::go(sf::Time frameTime) {
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());
    //The body is the one that contains the position, velocity, etc. not the body definition
    //screenHeight
    //Times 32, as 32 pixels is ~one meter
    position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)));
    //cout << physBody->GetPosition().x << " " << physBody->GetPosition().y << " " << physBodyDef.awake << endl;
}
