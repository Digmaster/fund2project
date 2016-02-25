#include "ExplodeScript.h"
#include <SFML/Graphics.hpp>

#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/SingleUseAnimatedComponent.h"
#include "Components/Audio/SingleUseAudioComponent.h"
#include "Components/ComponentManager.h"
#include "GameEngine.h"
#include "Physics/PhysicsEngine.h"
#include "Components/Stats/StatsComponent.h"

ExplodeScript::ExplodeScript()
{
    //ctor
}

ExplodeScript::~ExplodeScript()
{
    //dtor
}

int ExplodeScript::pixelsPerMeter = Options::instance().getPixelsPerMeter();
int ExplodeScript::numRays = 128;
float ExplodeScript::DEGTORAD = 0.0174533f;

ComponentBase::listenerList ExplodeScript::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&ExplodeScript::HandleMessage, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::DELETED, handler));
    return out;
}

void ExplodeScript::HandleMessage(Events event, EventObj* message, Entity* entity)
{
    switch(event)
    {
    case DELETED:
        unsigned int id = ComponentBase::getNewID();
        sf::Vector2f pos = entity->getPosition()->getPosition();
        Entity* bullet = new Entity(id);
        bullet->setPosition(std::make_shared<WorldPositionComponent>(pos, entity->getPosition()->getLayer()));
        bullet->setRender(std::make_shared<SingleUseAnimatedComponent>("Explosion", "Explode"));
        bullet->setAudio(std::make_shared<SingleUseAudioComponent>("assets/sound/explosion.wav"));
        ComponentManager::getInst().addEntity(id, bullet);
        raycastExplosion(pos, 100/pixelsPerMeter, 1);
    }
}

void ExplodeScript::raycastExplosion(sf::Vector2f location, float blastRadius, float power)
{

    b2Vec2 center;
    center.x = location.x/(float)pixelsPerMeter;
    center.y = location.y/(float)pixelsPerMeter * -1;

    for (int i = 0; i < numRays; i++) {
        float angle = (i / (float)numRays) * 360 * DEGTORAD;
        b2Vec2 rayDir( sinf(angle), cosf(angle) );
        b2Vec2 rayEnd = center + blastRadius * rayDir;

        //check what this ray hits
        RaycastObjectFound callback;//basic callback to record body and hit point
        callback.center = center;
        callback.power = power;
        callback.numRays = numRays;
        eng->physEng->_world->RayCast(&callback, center, rayEnd);
    }
}

float32 RaycastObjectFound::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
    if(fixture->IsSensor()) return 0;
    ExplodeScript::applyBlastImpulse(fixture->GetBody(), center, point, (power / (float)numRays));
    Entity* hit = ComponentManager::getInst()[((unsigned int)fixture->GetUserData())/10];
    if(hit!=nullptr && hit->getStats()!=nullptr)
    {
        hit->getStats()->modHealth(-1, hit);
    }
}

void ExplodeScript::applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower) {
    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();
    //ignore bodies exactly at the blast point - blast direction is undefined
    if ( distance == 0 )
        return;
    float invDistance = 1 / distance;
    float impulseMag = blastPower * invDistance * invDistance;
    body->ApplyLinearImpulse( impulseMag * blastDir, applyPoint, true );
}

void ExplodeScript::particalExplosion(sf::Vector2f location, float power)
{
    b2Vec2 center;
    center.x = location.x/pixelsPerMeter;
    center.y = location.y/pixelsPerMeter;

    for (int i = 0; i < numRays; i++) {
        float angle = (i / (float)numRays) * 360 * DEGTORAD;
        b2Vec2 rayDir( sinf(angle), cosf(angle) );

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true; // rotation not necessary
        bd.bullet = true; // prevent tunneling at high speed
        bd.linearDamping = 10; // drag due to moving through air
        bd.gravityScale = 0; // ignore gravity
        bd.position = center; // start at blast center
        bd.linearVelocity = power * rayDir;
        b2Body* body = eng->physEng->_world->CreateBody( &bd );

        b2CircleShape circleShape;
        circleShape.m_radius = 0.05; // very small

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = 60 / (float)numRays; // very high - shared across all particles
        fd.friction = 0; // friction not necessary
        fd.restitution = 0.99f; // high restitution to reflect off obstacles
        //fd.filter.groupIndex = -1; // particles should not collide with each other
        body->CreateFixture( &fd );
    }
}


