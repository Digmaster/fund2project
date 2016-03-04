#include "MissileWeapon.h"

#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/StaticSpriteComponent.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Script/KillScript.h"
#include "Components/Script/ExplodeScript.h"
#include "Components/Movement/AccelerateMovement.h"
#include "Components/Identification/IDComponent.h"


MissileWeapon::MissileWeapon(int damage, sf::Time cooldown)
{
    clipSize = -1;
    maxAmmo = -1;
    currClip = -1;
    currAmmo = -1;
    this->damage = damage;

    fireTimer = sf::Time::Zero;
    initalFireTimer = cooldown;
}

void MissileWeapon::fire(float angle, Entity* entity)
{
    if(entity->getIdentification()->getName()=="MainChar") std::cout << fireTimer.asSeconds() << " " << initalFireTimer.asSeconds() << std::endl;

    if(!canFire())
        return;
    unsigned int id = ComponentBase::getNewID();
    sf::Vector2f pos = entity->getPosition()->getPosition();
    pos.x += 40*std::cos(angle*0.0174532925);
    pos.y += -40*std::sin(angle*0.0174532925);
    Entity* bullet = new Entity(id);
    int bulletSpeed = 10;
    bullet->setPosition(std::make_shared<WorldPositionComponent>(pos, entity->getPosition()->getLayer(), (float)angle*0.0174532925));
    bullet->setRender(std::make_shared<StaticSpriteComponent>("assets/art/SuperMetroidSamus.png", sf::IntRect(423,29,16,6)));
    bullet->setPhysics(std::make_shared<SimpleBoxPhysics>(bullet->getID(), sf::Vector2f(10,5), 0, PhysicsOptions::isBullet, bullet->getPosition()));
    bullet->getPhysics()->getBody()->SetLinearVelocity(b2Vec2(std::cos((float)angle*0.0174532925)*bulletSpeed, std::sin((float)angle*0.0174532925)*bulletSpeed));
    bullet->getPhysics()->getBody()->SetGravityScale(0);
    bullet->addScript(std::make_shared<KillScript>(true, damage, sf::Time::Zero));
    bullet->addScript(std::make_shared<ExplodeScript>(damage/10));
    bullet->setMovement(std::make_shared<AccelerateMovement>(sf::Vector2f(std::cos((float)angle*0.0174532925)*bulletSpeed, std::sin((float)angle*0.0174532925)*bulletSpeed),100));
    bullet->setIdentification(entity->getIdentification());
    ComponentManager::getInst().addEntity(id, bullet);

    fireTimer = sf::Time(initalFireTimer);
    if(currClip!=-1) currClip--;
}
