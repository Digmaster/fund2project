#include "AccelerateMovement.h"
#include "Components/Physics/PhysicsComponent.h"


AccelerateMovement::AccelerateMovement(sf::Vector2f acceleration, float maxSpeed)
{
    this->acceleration = acceleration;
    this->maxSpeed = maxSpeed;
}
AccelerateMovement::AccelerateMovement(float angle, float ammount, float maxSpeed)
{
    float x = ammount*cos(angle);
    float y = ammount*sin(angle);
    AccelerateMovement(sf::Vector2f(x,y), maxSpeed);
}

void AccelerateMovement::go(sf::Time frameTime, Entity* entity)
{
    auto physics = entity->getPhysics();
    if(physics!=nullptr) {
        b2Body* body = physics->getBody();
        b2Vec2 velocity = body->GetLinearVelocity();

        body->ApplyForceToCenter(b2Vec2(acceleration.x-velocity.x*acceleration.x/maxSpeed,acceleration.y-velocity.y*acceleration.y/maxSpeed),true);
    }
}
