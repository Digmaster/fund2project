#ifndef PATHFOLLOWMOVEMENT_H
#define PATHFOLLOWMOVEMENT_H

#include <MovementComponent.h>
#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>


class PathFollowMovement : public MovementComponent
{
    public:
        PathFollowMovement();

        void go(sf::Time, Entity* entity);
    protected:
    private:
        std::vector<b2Vec2> movePath;
        bool pathClosed;
        int currentlyGoingTo;
        bool goingForward;
};

#endif // PATHFOLLOWMOVEMENT_H
