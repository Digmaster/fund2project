#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/ComponentManager.h"
#include "Options.h"
#include "physics/PhysicsEngine.h"
#include "GameEngine.h"

SimpleBoxPhysics::SimpleBoxPhysics(unsigned int ID, sf::Vector2f size, float friction, uint32 opts ) : PhysicsComponent(ID)
{
    leftListener = NULL;
    rightListener = NULL;
    headListener = NULL;
    footListener = NULL;
    if(opts & PhysicsOptions::isStatic)
        physBodyDef.type = b2_staticBody;
    else
        physBodyDef.type = b2_dynamicBody;
    physBodyDef.position.Set(1,1);
    physBodyDef.angle = 0;
    physBodyDef.fixedRotation = (opts & PhysicsOptions::notRotatable);
    physBody = eng->physEng->_world->CreateBody(&physBodyDef);
    if(opts & PhysicsOptions::roundedCorners) {
        b2Vec2 boxVertices[8];
        float ax = .5f*size.x/pixelsPerMeter;
        float ay = .5f*size.y/pixelsPerMeter;
        boxVertices[0].Set(-ax*.8f, -ay);
        boxVertices[1].Set(-ax, -ay*.8f);
        boxVertices[2].Set(ax*.8f, -ay);
        boxVertices[3].Set(ax, -ay*.8f);
        boxVertices[4].Set(ax, ay*.8f);
        boxVertices[5].Set(ax*.8f, ay);
        boxVertices[6].Set(-ax*.8f, ay);
        boxVertices[7].Set(-ax, ay*.8f);
        /*boxVertices[0].Set(-0.5f, -0.75f);
        boxVertices[1].Set(-0.25f, -0.975f);
        boxVertices[2].Set(0.25f, -0.975f);
        boxVertices[3].Set(0.5f, -0.75f);
        boxVertices[4].Set(0.5f, 0.9f);
        boxVertices[5].Set(0.4f, 0.975f);
        boxVertices[6].Set(-0.4f, 0.975f);
        boxVertices[7].Set(-0.5f, 0.9f);*/

        boxShape.Set(boxVertices, 8);
        footListener = NULL;
    }
    else {
        boxShape.SetAsBox(.5*size.x/pixelsPerMeter,.5*size.y/pixelsPerMeter);
    }
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = friction;
    boxFixtureDef.isSensor = (opts & PhysicsOptions::sensor);
    b2Fixture* fixture = physBody->CreateFixture(&boxFixtureDef);
    fixture->SetUserData( (void*)(getID()*10+0) );
    WorldPositionComponent* position = ComponentManager::getInst().posSym.getComponent(getID());

    if(opts & PhysicsOptions::sideSensors) { //All of the sensors!!!
        //foot
        boxShape.SetAsBox(size.x*.45/pixelsPerMeter, 0.1, b2Vec2(0,-size.y/(2.0f*pixelsPerMeter)), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* footSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        footSensorFixture->SetUserData( (void*)(getID()*10+1) );
        footListener = new FootContactListener(getID()*10+1);
        eng->physEng->contactListeners.addListener(footListener);
        //head
        boxShape.SetAsBox(size.x*.45/pixelsPerMeter, 0.1, b2Vec2(0,size.y/(2.0f*pixelsPerMeter)), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* headSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        headSensorFixture->SetUserData( (void*)(getID()*10+2) );
        headListener = new FootContactListener(getID()*10+2);
        eng->physEng->contactListeners.addListener(headListener);
        //left
        boxShape.SetAsBox(.1f, size.y*.35/pixelsPerMeter, b2Vec2(-size.x/(2.0f*pixelsPerMeter),0), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* leftSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        leftSensorFixture->SetUserData( (void*)(getID()*10+3) );
        leftListener = new FootContactListener(getID()*10+3);
        eng->physEng->contactListeners.addListener(leftListener);
        //right
        boxShape.SetAsBox(.1f, size.y*.35/pixelsPerMeter, b2Vec2(size.x/(2.0f*pixelsPerMeter),0), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* rightSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        rightSensorFixture->SetUserData( (void*)(getID()*10+4) );
        rightListener = new FootContactListener(getID()*10+4);
        eng->physEng->contactListeners.addListener(rightListener);
        //ladder
        ladderListener = new LadderContactListener(getID()*10+0, this);
        eng->physEng->contactListeners.addListener(ladderListener);
    }

    if(position!=NULL) {
        physBody->SetTransform(b2Vec2(position->getPosition().x/pixelsPerMeter, -position->getPosition().y/pixelsPerMeter),physBody->GetAngle());
    }
}

SimpleBoxPhysics::~SimpleBoxPhysics()
{
    //dtor
}

bool SimpleBoxPhysics::onGround() {
    if(footListener!=NULL)
        return footListener->onGround();
    else
        return true;
}

bool SimpleBoxPhysics::onLeft() {
    if(leftListener!=NULL)
        return leftListener->onGround();
    else
        return true;
}

bool SimpleBoxPhysics::onRight() {
    if(rightListener!=NULL)
        return rightListener->onGround();
    else
        return true;
}

bool SimpleBoxPhysics::onTop() {
    if(headListener!=NULL)
        return headListener->onGround();
    else
        return true;
}

bool SimpleBoxPhysics::overLadder() {
    if(ladderListener!=NULL)
        return ladderListener->overLadder();
    else
        return false;
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


void FootContactListener::BeginContact(b2Contact* contact) {
  //check if fixture A was the foot sensor
  void* fixtureUserData = contact->GetFixtureA()->GetUserData();
  if ( (unsigned int)fixtureUserData == findID )
    if( !contact->GetFixtureB()->IsSensor())
      onGroundNum++;
  //check if fixture B was the foot sensor
  fixtureUserData = contact->GetFixtureB()->GetUserData();
  if ( (unsigned int)fixtureUserData == findID )
    if(!contact->GetFixtureA()->IsSensor())
      onGroundNum++;
}

void FootContactListener::EndContact(b2Contact* contact) {
  //check if fixture A was the foot sensor
  void* fixtureUserData = contact->GetFixtureA()->GetUserData();
  if ( (unsigned int)fixtureUserData == findID )
    if(!contact->GetFixtureB()->IsSensor())
      onGroundNum--;
  //check if fixture B was the foot sensor
  fixtureUserData = contact->GetFixtureB()->GetUserData();
  if ( (unsigned int)fixtureUserData == findID )
    if(!contact->GetFixtureA()->IsSensor())
      onGroundNum--;
}

void LadderContactListener::BeginContact(b2Contact* contact) {
  //check if fixture A was the foot sensor
  unsigned int fixtureUserDataA = (unsigned int)contact->GetFixtureA()->GetUserData();
  unsigned int fixtureUserDataB = (unsigned int)contact->GetFixtureB()->GetUserData();
  IDComponent* idCompA = ComponentManager::getInst().idSym.getComponent(fixtureUserDataA/10); //The findID is ID*10+fixture number (Which is defined as whatever). Divide by ten to get the actual ID
  IDComponent* idCompB = ComponentManager::getInst().idSym.getComponent(fixtureUserDataB/10);

    string nameA;
    string nameB;

    if(idCompA != NULL){
        nameA = idCompA->getType();
    }

    if(idCompB != NULL){
        nameB = idCompB->getType();
    }



  if ( fixtureUserDataA == findID || fixtureUserDataB == findID){
//std::cout << "LadderListerner BeginContact" << std::endl;
    if( contact->GetFixtureA()->IsSensor() && nameA == "ladder" && (contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody)){
      overLadderNum++;
    }
      if( contact->GetFixtureB()->IsSensor() && nameB == "ladder" && (contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)){
      overLadderNum++;
      }
    }

}

void LadderContactListener::EndContact(b2Contact* contact) {

    unsigned int fixtureUserDataA = (unsigned int)contact->GetFixtureA()->GetUserData();
    unsigned int fixtureUserDataB = (unsigned int)contact->GetFixtureB()->GetUserData();

    IDComponent* idCompA = ComponentManager::getInst().idSym.getComponent(fixtureUserDataA/10);
    IDComponent* idCompB = ComponentManager::getInst().idSym.getComponent(fixtureUserDataB/10);

    string nameA;
    string nameB;
    if(idCompA)
        nameA = idCompA->getType();
    if(idCompB)
        nameB = idCompB->getType();

  if ( fixtureUserDataA == findID || fixtureUserDataB == findID){
    if( contact->GetFixtureA()->IsSensor() && nameA == "ladder"  && (contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody)){
        overLadderNum--;
    }
    if( contact->GetFixtureB()->IsSensor() && nameB == "ladder" && (contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)){
        overLadderNum--;
    }
    }
}

