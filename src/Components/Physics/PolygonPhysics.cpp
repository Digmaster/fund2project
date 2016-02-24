#include "Components/Physics/PolygonPhysics.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "GameEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"

PolygonPhysics::PolygonPhysics(unsigned int ID, std::vector<sf::Vector2i> points, uint32 opts, std::shared_ptr<WorldPositionComponent> position) : PhysicsComponent()
{
    physBodyDef.type = b2_staticBody;
    physBody = eng->physEng->_world->CreateBody(&physBodyDef);

    if(opts & PhysicsOptions::isStatic)
        physBodyDef.type = b2_staticBody;
    else
        physBodyDef.type = b2_dynamicBody;

    physBodyDef.fixedRotation = (opts & PhysicsOptions::notRotatable);

    headListener = new FootContactListener(ID*10);

    b2Vec2 *polygons = new b2Vec2[points.size()];
    for (unsigned int i=0; i < points.size(); i++){
        polygons[i].Set( points[i].x/pixelsPerMeter, -points[i].y/pixelsPerMeter );
    }

    boundaryShape.Set(polygons, points.size());
    boundaryFixtureDef.shape = &boundaryShape;
    boundaryFixtureDef.friction = 10;
    boundaryFixtureDef.isSensor = opts & PhysicsOptions::sensor;
    b2Fixture* fixture = physBody->CreateFixture(&boundaryFixtureDef);
    fixture->SetUserData( (void*)(ID*10+2) );

    if(position!=NULL) {
        physBodyDef.angle = position->getRotation();
        physBody->SetTransform(b2Vec2(position->getPosition().x/pixelsPerMeter, -position->getPosition().y/pixelsPerMeter),physBody->GetAngle());
    }
}

PolygonPhysics::~PolygonPhysics()
{
    eng->physEng->_world->DestroyBody(physBody);
}

std::vector<b2Vec2> PolygonPhysics::getPath()
{
    std::vector<b2Vec2> out;
    for(int i = 0; i < boundaryShape.GetVertexCount(); i++)
    {
        b2Vec2 curr = boundaryShape.GetVertex(i);
        // Translate from box2D space to game space
        curr.x *= pixelsPerMeter;
        curr.y *= pixelsPerMeter;
        curr.y *= -1;
        out.push_back(curr);
    }
    return out;
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
    std::shared_ptr<WorldPositionComponent> position = entity->getPosition();

    //Times 32, as 32 pixels is ~one meter
    position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)), this);
}
