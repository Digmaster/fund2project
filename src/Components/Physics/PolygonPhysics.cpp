#include "Components/Physics/PolygonPhysics.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "GameEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"

PolygonPhysics::PolygonPhysics(unsigned int ID, std::vector<sf::Vector2i> points) : PhysicsComponent()
{
    physBodyDef.type = b2_staticBody;
    physBody = eng->physEng->_world->CreateBody(&physBodyDef);

    headListener = new FootContactListener(ID*10);

    b2Vec2 *polygons = new b2Vec2[points.size()];
    for (unsigned int i=0; i < points.size(); i++){
        polygons[i].Set( points[i].x/pixelsPerMeter, -points[i].y/pixelsPerMeter );
    }

    boundaryShape.Set(polygons, points.size());
    boundaryFixtureDef.shape = &boundaryShape;
    boundaryFixtureDef.friction = 10;
    b2Fixture* fixture = physBody->CreateFixture(&boundaryFixtureDef);
    fixture->SetUserData( (void*)(ID*10+2) );
    //screenHeight = atoi(Options::instance().get("screen_height").c_str());
}

PolygonPhysics::~PolygonPhysics()
{
    eng->physEng->_world->DestroyBody(physBody);
}

bool PolygonPhysics::onTop() {
    if(headListener!=NULL)
        return headListener->onGround();
    else
        return true;
}

unsigned int PolygonPhysics::touchingTop() {
    if(headListener!=NULL)
        return headListener->getTouching();
    else
        return true;
}

void PolygonPhysics::go(sf::Time frameTime, Entity* entity) {
    WorldPositionComponent* position = entity->position;

    //Times 32, as 32 pixels is ~one meter
    position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)), this);
}
