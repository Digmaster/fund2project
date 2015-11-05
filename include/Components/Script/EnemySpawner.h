#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Components/Script/ScriptComponent.h"
#include <SFML/Graphics.hpp>


class EnemySpawner : public ScriptComponent
{
    public:
        /** Default constructor */
        EnemySpawner();
        EnemySpawner(sf::Sprite spr, sf::Time frequency, int max, int range);
        /** Default destructor */
        virtual ~EnemySpawner();

        virtual void go(sf::Time frameTime, Entity* entity);
    protected:
    private:
        sf::Time freq;
        sf::Time countdown;
        int max;
        int curr;
        int range;
        sf::Sprite spr;
};

#endif // ENEMYSPAWNER_H
