#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/ComponentManager.h"
#include "Options.h"
#include "physics/PhysicsEngine.h"
#include "GameEngine.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Entity.h"

#include "Components/Stats/StatsComponent.h"

SimpleBoxPhysics::SimpleBoxPhysics(unsigned int ID, sf::Vector2f size, float friction, uint32 opts, std::shared_ptr<WorldPositionComponent> position ) : PhysicsComponent()
{
    leftListener = NULL;
    rightListener = NULL;
    headListener = NULL;
    footListener = NULL;
    bodyListener = NULL;
    if(opts & PhysicsOptions::isStatic)
        physBodyDef.type = b2_staticBody;
    else if (opts & PhysicsOptions::isKinematic)
        physBodyDef.type = b2_kinematicBody;
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

    //body sensor
    fixture->SetUserData( (void*)(ID*10+0) );
    bodyListener = new FootContactListener(ID*10+0);
    eng->physEng->contactListeners.addListener(bodyListener);

    if(opts & PhysicsOptions::sideSensors) { //All of the sensors!!!
        //foot
        b2PolygonShape sensorShape;
        boxFixtureDef.shape = &sensorShape;

        sensorShape.SetAsBox(size.x*.45/pixelsPerMeter, 0.1, b2Vec2(0,-size.y/(2.0f*pixelsPerMeter)), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* footSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        footSensorFixture->SetUserData( (void*)(ID*10+1) );
        footListener = new FootContactListener(ID*10+1);
        eng->physEng->contactListeners.addListener(footListener);
        //head
        sensorShape.SetAsBox(size.x*.45/pixelsPerMeter, 0.1, b2Vec2(0,size.y/(2.0f*pixelsPerMeter)), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* headSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        headSensorFixture->SetUserData( (void*)(ID*10+2) );
        headListener = new FootContactListener(ID*10+2);
        eng->physEng->contactListeners.addListener(headListener);
        //left
        sensorShape.SetAsBox(.1f, size.y*.35/pixelsPerMeter, b2Vec2(-size.x/(2.0f*pixelsPerMeter),0), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* leftSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        leftSensorFixture->SetUserData( (void*)(ID*10+3) );
        leftListener = new FootContactListener(ID*10+3);
        eng->physEng->contactListeners.addListener(leftListener);
        //right
        sensorShape.SetAsBox(.1f, size.y*.35/pixelsPerMeter, b2Vec2(size.x/(2.0f*pixelsPerMeter),0), 0);
        boxFixtureDef.isSensor = true;
        b2Fixture* rightSensorFixture = physBody->CreateFixture(&boxFixtureDef);
        rightSensorFixture->SetUserData( (void*)(ID*10+4) );
        rightListener = new FootContactListener(ID*10+4);
        eng->physEng->contactListeners.addListener(rightListener);
        //ladder
        ladderListener = new LadderContactListener(ID*10+0, this);
        eng->physEng->contactListeners.addListener(ladderListener);
    }

    if(position!=NULL) {
        physBody->SetTransform(b2Vec2(position->getPosition().x/pixelsPerMeter, -position->getPosition().y/pixelsPerMeter),physBody->GetAngle());
    }
}

ComponentBase::listenerList SimpleBoxPhysics::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&SimpleBoxPhysics::HandleMessage, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::HEALTH_CHANGE, handler));
    return out;
}

void SimpleBoxPhysics::HandleMessage(Events event, EventObj* message, Entity* entity)
{
    switch(event)
    {
    case HEALTH_CHANGE:
        HealthChange* obj = (HealthChange*)message;
//        if(obj->causer->getPosition()!=nullptr && entity->getPosition()!=nullptr)
//        {
//            float yDif = entity->getPosition()->getPosition().y-obj->causer->getPosition()->getPosition().y;
//            float xDif = entity->getPosition()->getPosition().x-obj->causer->getPosition()->getPosition().x;
//            if(xDif==0) xDif=.1;
//            float angle = atan2(yDif,xDif) * -180.0f/3.14159265f;
//            if(physBody!=nullptr) physBody->ApplyForceToCenter(b2Vec2(-std::cos((float)angle*0.0174532925)*1000, -std::sin((float)angle*0.0174532925)*1000), true);
//        }
    }
}

bool SimpleBoxPhysics::onGround() {
    if(footListener!=NULL)
        return footListener->onGround();
    else
        return true;
}

unsigned int SimpleBoxPhysics::touchingGround() {
    if(footListener!=NULL)
        return footListener->getTouching();
    else
        return true;
}

bool SimpleBoxPhysics::onLeft() {
    if(leftListener!=NULL)
        return leftListener->onGround();
    else
        return true;
}

unsigned int SimpleBoxPhysics::touchingLeft() {
    if(leftListener!=NULL)
        return leftListener->getTouching();
    else
        return true;
}

bool SimpleBoxPhysics::onRight() {
    if(rightListener!=NULL)
        return rightListener->onGround();
    else
        return true;
}

unsigned int SimpleBoxPhysics::touchingRight() {
    if(rightListener!=NULL) {
        return rightListener->getTouching();
    }
    else
        return true;
}

bool SimpleBoxPhysics::onTop() {
    if(headListener!=NULL)
        return headListener->onGround();
    else
        return true;
}

unsigned int SimpleBoxPhysics::touchingTop() {
    if(headListener!=NULL)
        return headListener->getTouching();
    else
        return true;
}

bool SimpleBoxPhysics::onBody() {
    if(bodyListener!=NULL)
        return bodyListener->onGround();
    else
        return true;
}

unsigned int SimpleBoxPhysics::touchingBody() {
    if(bodyListener!=NULL)
        return bodyListener->getTouching();
    else
        return true;
}

bool SimpleBoxPhysics::overLadder() {
    if(ladderListener!=NULL)
        return ladderListener->overLadder();
    else
        return false;
}

void SimpleBoxPhysics::go(sf::Time frameTime, Entity* entity) {
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

std::vector<b2Vec2> SimpleBoxPhysics::getPath()
{
    std::vector<b2Vec2> out;
    for(int i = 0; i < boxShape.GetVertexCount(); i++)
    {
        b2Vec2 curr = boxShape.GetVertex(i);
        // Translate from box2D space to game space
        curr.x *= pixelsPerMeter;
        curr.y *= pixelsPerMeter;
        curr.y *= -1;
        out.push_back(curr);
    }
    return out;
}


void FootContactListener::BeginContact(b2Contact* contact) {
  //check if fixture A was the foot sensor
  void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
  void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();
  if ( (unsigned int)fixtureUserDataA == findID )
    if( !contact->GetFixtureB()->IsSensor()) {
      onGroundNum++;
      if((unsigned int)fixtureUserDataB!=0) {
        lastTouch = (unsigned int)fixtureUserDataB/10;
      }
      return;
    }
  //check if fixture B was the foot sensor
  if ( (unsigned int)fixtureUserDataB == findID )
    if(!contact->GetFixtureA()->IsSensor()) {
      onGroundNum++;
      if((unsigned int)fixtureUserDataA!=0)
        lastTouch = (unsigned int)fixtureUserDataA/10;
      return;
    }
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

    Entity* entA = ComponentManager::getInst()[fixtureUserDataA/10];
    Entity* entB = ComponentManager::getInst()[fixtureUserDataB/10];

    if(entA==nullptr || entB==nullptr) return;

    std::shared_ptr<IDComponent> idCompA = entA->getIdentification(); //The findID is ID*10+fixture number (Which is defined as whatever). Divide by ten to get the actual ID
    std::shared_ptr<IDComponent> idCompB = entB->getIdentification();

    std::string nameA;
    std::string nameB;

    if(idCompA != NULL){
        nameA = idCompA->getType();
    }

    if(idCompB != NULL){
        nameB = idCompB->getType();
    }

    if ( fixtureUserDataA == findID || fixtureUserDataB == findID)
    {
        if(    (contact->GetFixtureA()->IsSensor() && nameA == "ladder" && contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody)
           ||  (contact->GetFixtureB()->IsSensor() && nameB == "ladder" && contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody))
        {
            overLadderNum++;
        }
    }

}

void LadderContactListener::EndContact(b2Contact* contact) {

    unsigned int fixtureUserDataA = (unsigned int)contact->GetFixtureA()->GetUserData();
    unsigned int fixtureUserDataB = (unsigned int)contact->GetFixtureB()->GetUserData();

    Entity* entA = ComponentManager::getInst()[fixtureUserDataA/10];
    Entity* entB = ComponentManager::getInst()[fixtureUserDataB/10];

    if(entA==nullptr || entB==nullptr) return;

    std::shared_ptr<IDComponent> idCompA = entA->getIdentification(); //The findID is ID*10+fixture number (Which is defined as whatever). Divide by ten to get the actual ID
    std::shared_ptr<IDComponent> idCompB = entB->getIdentification();

    std::string nameA;
    std::string nameB;

    if(idCompA != NULL){
        nameA = idCompA->getType();
    }

    if(idCompB != NULL){
        nameB = idCompB->getType();
    }

    if ( fixtureUserDataA == findID || fixtureUserDataB == findID)
    {
        if(    (contact->GetFixtureA()->IsSensor() && nameA == "ladder" && contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody)
           ||  (contact->GetFixtureB()->IsSensor() && nameB == "ladder" && contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody))
        {
            overLadderNum--;
        }
    }
}

