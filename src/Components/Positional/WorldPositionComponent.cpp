#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Options.h"

WorldPositionComponent::WorldPositionComponent(unsigned int ID, sf::Vector2f Position, int Layer, float Rotation) : ComponentBase(ID) {
    compMan->posSym.addComponent(this);
    setPosition(Position);
    setRotation(Rotation);
    setLayer(Layer);
}

int WorldPositionComponent::PPM = atoi(Options::instance().get("pixels_per_meter").c_str());

void WorldPositionComponent::go(sf::Time frameTime) {
    //This doesn't really need to do anything to be honest.
}

void WorldPositionComponent::setPosition(sf::Vector2f input, bool awaken) {
    position = input;
    PhysicsComponent* phys = compMan->physSym.getComponent(getID());
    if(phys!=NULL) {
        phys->getBody()->SetTransform(b2Vec2(position.x/PPM, -position.y/PPM),phys->getBody()->GetAngle());
        if(awaken) {
            phys->getBody()->SetAwake(true);
        }
    }
}

void WorldPositionComponent::move(sf::Vector2f input, bool awaken) {
    sf::Vector2f newPos;
    newPos.x = position.x + input.x;
    newPos.y = position.y + input.y;
    setPosition(newPos, awaken);
}

void WorldPositionComponent::setRotation(float input, bool awaken) {
    rotation = input;
    PhysicsComponent* phys = compMan->physSym.getComponent(getID());
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
