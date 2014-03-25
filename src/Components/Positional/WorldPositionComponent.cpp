#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"

WorldPositionComponent::WorldPositionComponent(unsigned int ID) : ComponentBase(ID) {
    compMan->posSym.addComponent(this);
    position.x=0;
    position.y=0;
    rotation=0;
    layer=0;
}

void WorldPositionComponent::go(sf::Time frameTime) {
    /* //Updates position based on velocity of physics component
    auto_ptr phys = ComponentManager::getInst().physSym.getComponent(getID())
    if(phys != NULL) { //ALWAYS FUCKING CHECK IF IT RETURNS NULLLLLLLLLLLLLLLLLL
        sf::FloatRect velocity phys->getVelocity();
        position.x *= velocity.x * frameTime;
        position.y *= velocity.y * frametime;
    }
    */
}

void WorldPositionComponent::setPosition(sf::Vector2f input, bool awaken) {
    position = input;
    PhysicsComponent* phys = compMan->physSym.getComponent(getID());
    if(phys!=NULL) {
        phys->getBody()->SetTransform(b2Vec2(position.x/32, -position.y/32),phys->getBody()->GetAngle());
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
