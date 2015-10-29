#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Options.h"

WorldPositionComponent::WorldPositionComponent(sf::Vector2f Position, int Layer, float Rotation) : ComponentBase() {
    setPosition(Position);
    setRotation(Rotation);
    setLayer(Layer);
}

WorldPositionComponent::WorldPositionComponent(WorldPositionComponent& old)
{
    setPosition(sf::Vector2f(old.getPosition()));
    setLayer(old.getLayer());
    setRotation(old.getRotation());
}

int WorldPositionComponent::PPM = atoi(Options::instance().get("pixels_per_meter").c_str());

void WorldPositionComponent::go(sf::Time frameTime, Entity* entity) {
    //This doesn't really need to do anything to be honest.
}

void WorldPositionComponent::setPosition(sf::Vector2f input, PhysicsComponent* phys, bool awaken) {
    position = input;
    if(phys!=NULL) {
        phys->getBody()->SetTransform(b2Vec2(position.x/PPM, -position.y/PPM),phys->getBody()->GetAngle());
        if(awaken) {
            phys->getBody()->SetAwake(true);
        }
    }
}

void WorldPositionComponent::move(sf::Vector2f input, PhysicsComponent* phys, bool awaken) {
    sf::Vector2f newPos;
    newPos.x = position.x + input.x;
    newPos.y = position.y + input.y;
    setPosition(newPos, phys, awaken);
}

void WorldPositionComponent::setRotation(float input, PhysicsComponent* phys, bool awaken) {
    rotation = input;
    if(phys!=NULL) {
        phys->getBody()->SetTransform(phys->getBody()->GetPosition(),rotation);
        if(awaken) {
            phys->getBody()->SetAwake(true);
        }
    }
}

int WorldPositionComponent::getLayer() {
    return layer;
}

void WorldPositionComponent::setLayer(int input) {
    layer = input;
}
