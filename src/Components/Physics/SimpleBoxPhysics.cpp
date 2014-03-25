#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/ComponentManager.h"
#include "Options.h"

SimpleBoxPhysics::SimpleBoxPhysics(unsigned int ID, int x, int y, bool isStatic, bool rotatable, bool roundedCorners, bool isSensor) : PhysicsComponent(ID)
{
    if(isStatic)
        physBodyDef.type = b2_staticBody;
    else
        physBodyDef.type = b2_dynamicBody;
    physBodyDef.position.Set(1,1);
    physBodyDef.angle = 0;
    physBodyDef.fixedRotation = !rotatable;
    physBody = _world->CreateBody(&physBodyDef);
    if(roundedCorners) {
        b2Vec2 boxVertices[8];
        boxVertices[0].Set(-0.5f, -0.75f);
        boxVertices[1].Set(-0.25f, -0.975f);
        boxVertices[2].Set(0.25f, -0.975f);
        boxVertices[3].Set(0.5f, -0.75f);
        boxVertices[4].Set(0.5f, 0.9f);
        boxVertices[5].Set(0.4f, 0.975f);
        boxVertices[6].Set(-0.4f, 0.975f);
        boxVertices[7].Set(-0.5f, 0.9f);

        boxShape.Set(boxVertices, 8);
    }
    else {
        boxShape.SetAsBox(.5*x/pixelsPerMeter,.5*y/pixelsPerMeter);
    }
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 1;
    boxFixtureDef.isSensor = isSensor;
    physBody->CreateFixture(&boxFixtureDef);
    screenHeight = atoi(Options::instance().get("screen_height").c_str());
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());

    //add foot sensor fixture
    /*b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.3, 0.3, b2Vec2(0,-2), 0);
    b2FixtureDef myFixtureDef;
    myFixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = physBody->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );
    */

    if(position!=NULL) {
        physBody->SetTransform(b2Vec2(position->getPosition().x/pixelsPerMeter, -position->getPosition().y/pixelsPerMeter),physBody->GetAngle());
    }
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
    position->setPosition(sf::Vector2f((physBody->GetPosition().x)*pixelsPerMeter, -((physBody->GetPosition().y)*pixelsPerMeter)),false);
    position->setRotation(physBody->GetAngle());
    //cout << physBody->GetPosition().x << " " << physBody->GetPosition().y << " " << physBodyDef.awake << endl;
}

void SimpleBoxPhysics::setRotatable(bool input) {
    //physBodyDef.fixedRotation = !input;
}
