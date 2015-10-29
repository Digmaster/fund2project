#include "Components/Physics/BoundaryPhysics.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"
#include "GameEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"

BoundaryPhysics::BoundaryPhysics(int ID, float x, float y, float endx, float endy) : PhysicsComponent()
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
    fixture->SetUserData( (void*)(ID*10+2) );
    //screenHeight = atoi(Options::instance().get("screen_height").c_str());
}

BoundaryPhysics::~BoundaryPhysics()
{
    eng->physEng->_world->DestroyBody(physBody);
}

void BoundaryPhysics::go(sf::Time frameTime, Entity* entity) {
    WorldPositionComponent* position = entity->position;

    //Times 32, as 32 pixels is ~one meter
    if(position) //IMPORTANT!!! YOU NEVER KNOW IF A COMPONENT EXISTS, SO CHECK FOR IT!
        position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)), this);
}
