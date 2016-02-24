#include "Components/Physics/EllipsePhysics.h"
#include "Components/ComponentManager.h"
#include "Options.h"
#include "physics/PhysicsEngine.h"
#include "GameEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"

#include "Components/Stats/StatsComponent.h"


EllipsePhysics::EllipsePhysics(unsigned int ID, sf::Vector2f size, float friction, uint32 opts, std::shared_ptr<WorldPositionComponent> position ) : PhysicsComponent()
{
    float ax = size.x/pixelsPerMeter;
    float ay = size.y/pixelsPerMeter;
    //createEllipse(ax, ay, friction, opts);
    createCircle(ax/2, friction, position, opts);
    radius = ax/2;

    if(position!=NULL) {
        physBody->SetTransform(b2Vec2(position->getPosition().x/pixelsPerMeter, -position->getPosition().y/pixelsPerMeter),physBody->GetAngle());
    }
}

void EllipsePhysics::go(sf::Time frameTime, Entity* entity) {
    std::shared_ptr<WorldPositionComponent> position = entity->getPosition();
    //The body is the one that contains the position, velocity, etc. not the body definition
    //screenHeight
    //Times 32, as 32 pixels is ~one meter
    if(position) {
        position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)), this, false);
        position->setRotation(physBody->GetAngle(), this);
    }
    //cout << physBody->GetPosition().x << " " << physBody->GetPosition().y << " " << physBodyDef.awake << endl;
}

void EllipsePhysics::createCircle(float r, float friction, std::shared_ptr<WorldPositionComponent> position, uint32 opts)
{
    if(opts & PhysicsOptions::isStatic)
        physBodyDef.type = b2_staticBody;
    else
        physBodyDef.type = b2_dynamicBody;
    if(opts & PhysicsOptions::isBullet)
        physBodyDef.bullet = true;
    physBodyDef.position.Set(1,1);

    if(position!=nullptr)
        physBodyDef.angle = position->getRotation();
    else
        physBodyDef.angle = 0;

    physBodyDef.fixedRotation = (opts & PhysicsOptions::notRotatable);
    physBody = eng->physEng->_world->CreateBody(&physBodyDef);

    circleShape.m_p.Set(0.0f, 0.0f);
    circleShape.m_radius = r;

    circleFixtureDef.shape = &circleShape;
    circleFixtureDef.density = 1;
    circleFixtureDef.restitution = 0;
    circleFixtureDef.friction = friction;
    circleFixtureDef.isSensor = (opts & PhysicsOptions::sensor);
    b2Fixture* fixture = physBody->CreateFixture(&circleFixtureDef);

    fixture->SetUserData( (void*)(ID*10+0) );
}

void EllipsePhysics::createEllipse(float x, float y, float friction, uint32 opts)
{
    const float32 INNER_RADIUS = x;
    const float32 OUTER_RADIUS = y;
    const float32 BALL_RADIUS = 0.1;
    const uint32 DIVISIONS = 36;

    // Create the body.
    b2BodyDef bodyDef;
    bodyDef.position.Set(0,0);
    bodyDef.type = b2_dynamicBody;
    physBody = eng->physEng->_world->CreateBody(&bodyDef);
    assert(physBody != NULL);

    // Now attach fixtures to the body.
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0;
    fixtureDef.restitution = 0.9;
    fixtureDef.friction = friction;
    fixtureDef.isSensor = (opts & PhysicsOptions::sensor);
    b2Fixture* fixture = physBody->CreateFixture(&fixtureDef);
    fixture->SetUserData( (void*)(ID*10+0) );

    // Inner circle.
    b2CircleShape circleShape;
    circleShape.m_radius = INNER_RADIUS;
    fixtureDef.shape = &circleShape;
    physBody->CreateFixture(&fixtureDef);

    // Outer shape.
    b2ChainShape chainShape;
    std::vector<b2Vec2> vertices;
    const float32 SPIKE_DEGREE = 2*3.14/180;
    for(int idx = 0; idx < DIVISIONS; idx++)
    {
        float32 angle = ((3.14*2)/DIVISIONS)*idx;
        float32 xPos, yPos;

        xPos = OUTER_RADIUS*cosf(angle);
        yPos = OUTER_RADIUS*sinf(angle);
        vertices.push_back(b2Vec2(xPos,yPos));
    }
    vertices.push_back(vertices[0]);
    chainShape.CreateChain(&vertices[0], vertices.size());
    fixtureDef.shape = &chainShape;
    b2Fixture* fixture2 = physBody->CreateFixture(&fixtureDef);
    fixture2->SetUserData( (void*)(ID*10+0) );
}

std::vector<b2Vec2> EllipsePhysics::getPath()
{
    std::vector<b2Vec2> out;
    int MAX_SEGMENTS = 32;
    for(int i = 0; i < MAX_SEGMENTS; i++)
    {
        float mr = radius*pixelsPerMeter;
        double angle = 3.14f*2.0f*((double)i/(double)MAX_SEGMENTS);
        out.push_back(b2Vec2(mr*cos(angle),mr*sin(angle)));
    }
    return out;
}
