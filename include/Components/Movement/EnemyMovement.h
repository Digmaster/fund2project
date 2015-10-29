#ifndef ENEMYMOVEMENT_H
#define ENEMYMOVEMENT_H

#include "Components/Movement/MovementComponent.h"

class EnemyMovement : public MovementComponent
{
    public:
        EnemyMovement();
        ~EnemyMovement() {}
        void go(sf::Time frameTime, Entity* entity);
        std::string getCurrentMovement();
    protected:
    private:
        sf::Time jumpTimer;
        sf::Time walkTimer;
};

#endif // ENEMYMOVEMENT_H
