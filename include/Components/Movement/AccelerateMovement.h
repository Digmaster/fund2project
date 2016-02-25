#ifndef ACCELERATEMOVEMENT_H
#define ACCELERATEMOVEMENT_H

#include <MovementComponent.h>

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>

class AccelerateMovement : public MovementComponent
{
    public:
        AccelerateMovement(sf::Vector2f acceleration, float maxSpeed);
        AccelerateMovement(float angle, float ammount, float maxSpeed);

        void go(sf::Time, Entity* entity);
    protected:
    private:
        sf::Vector2f acceleration;
        float maxSpeed;
};

#endif // ACCELERATEMOVEMENT_H
