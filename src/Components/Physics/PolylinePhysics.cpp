#include "Components/Physics/PolylinePhysics.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"
#include "GameEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"

PolylinePhysics::PolylinePhysics(unsigned int ID, std::vector<sf::Vector2i> points) : PhysicsComponent()
{
    physBodyDef.type = b2_staticBody;
    physBody = eng->physEng->_world->CreateBody(&physBodyDef);

    b2Vec2 *polygons = new b2Vec2[points.size()];
    for (int i=0; i < points.size(); i++){
        polygons[i].Set( points[i].x/pixelsPerMeter, -points[i].y/pixelsPerMeter );
    }

    polylineChain.CreateChain(polygons, points.size());
    boundaryFixtureDef.shape = &polylineChain;
    boundaryFixtureDef.friction = 10;
    b2Fixture* fixture = physBody->CreateFixture(&boundaryFixtureDef);
    fixture->SetUserData( (void*)(ID*10+2) );
    //screenHeight = atoi(Options::instance().get("screen_height").c_str());
}

PolylinePhysics::~PolylinePhysics()
{
    eng->physEng->_world->DestroyBody(physBody);
}

void PolylinePhysics::go(sf::Time frameTime, Entity* entity) {
    WorldPositionComponent* position = entity->position;
    //The body is the one that contains the position, velocity, etc. not the body definition
    //screenHeight
    //Times 32, as 32 pixels is ~one meter
    position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)), this);
    //cout << physBody->GetPosition().x << " " << physBody->GetPosition().y << " " << physBodyDef.awake << endl;
}
