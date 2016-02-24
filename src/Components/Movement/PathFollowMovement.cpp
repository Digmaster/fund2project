#include "PathFollowMovement.h"
#include "Components/ComponentManager.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"

PathFollowMovement::PathFollowMovement()
{
    currentlyGoingTo = 0;
    goingForward = true;
}

void PathFollowMovement::go(sf::Time frameTime, Entity* entity)
{
    if(entity->getTarget()==nullptr)
    {
        movePath.clear();
        return;
    }
    else
    {
        Entity* target = ComponentManager::getInst()[entity->getTarget()->getTarget()];
        if(target!=nullptr)
        {
            if(movePath.size()==0 && target->getPhysics()!=nullptr)
            {
                std::shared_ptr<PhysicsComponent> phys = target->getPhysics();

                movePath = phys->getPath();
                pathClosed = phys->isPathClosed();
                currentlyGoingTo = 0;
                entity->getPosition()->setPosition(target->getPosition()->getPosition());
            }
            auto pos = target->getPosition();
            auto selfPos = entity->getPosition();
            if(pos!=nullptr)
            {
                b2Vec2 nextSpot = movePath.at(currentlyGoingTo);
                nextSpot.x += pos->getPosition().x;
                nextSpot.y += pos->getPosition().y;

                //If point very close, move onto next point
                float x = nextSpot.x-selfPos->getPosition().x;
                float y = nextSpot.y-selfPos->getPosition().y;
                if(x==0) x=.001;

                float angle = atan2(y, x);
                float normFactor = (float)frameTime.asMicroseconds()/10000.0f; //move one pixel every 1/100th of a second;
                float speed = 1;

                sf::Vector2f movement = sf::Vector2f(speed*normFactor*cos(angle), speed*normFactor*sin(angle));

                selfPos->move(movement, entity->getPhysics().get());

                //Move anything on top of the platform as well
                if(entity->getPhysics() && entity->getPhysics()->onTop())
                {
                    Entity* topEnt = ComponentManager::getInst()[entity->getPhysics()->touchingTop()];
                    if(topEnt!=nullptr && topEnt->getPosition()!=nullptr)
                    {
                        topEnt->getPosition()->move(movement, topEnt->getPhysics().get());
                    }
                }

                if((x*x+y*y)<(1*1)) //very close to next target
                {
                    if(pathClosed)
                        currentlyGoingTo = (currentlyGoingTo+1)%(movePath.size());
                    else
                    {
                        if(goingForward)
                        {
                            currentlyGoingTo += 1;
                            if(currentlyGoingTo == movePath.size())
                            {
                                currentlyGoingTo-=2;
                                goingForward = false;
                            }
                        }
                        else
                        {
                            currentlyGoingTo -= 1;
                            if(currentlyGoingTo == -1)
                            {
                                currentlyGoingTo+=2;
                                goingForward = true;
                            }
                        }
                    }
                }

                //std::cout << selfPos->getPosition().x << " " << selfPos->getPosition().y << " " << currentlyGoingTo << " " << movePath.size() << std::endl;
            }
        }
    }
}
