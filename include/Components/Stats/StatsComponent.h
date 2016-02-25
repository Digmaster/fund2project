#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H

#include "Components/ComponentBase.h"


class StatsComponent : public ComponentBase
{
    public:
        StatsComponent(int initHealth, int maxHealth = -1);
        /** Default destructor */
        virtual ~StatsComponent();
        virtual void go(sf::Time frameTime, Entity* entity);

        int getHealth();
        void setHealth(int, Entity*);
        void modHealth(int, Entity*);
        bool isDead();

        float getSpeed() {return speedMod;}
        void setSpeed(float f) {speedMod = f;}
        float getRunMod() {return runMod;}
        void setRunMod(float f) {runMod = f;}
    protected:
    private:
        int health;
        int maxHealth;
        bool dead;
        Entity* _listenedEntity;
        float speedMod;
        float runMod;
};

#endif // STATSCOMPONENT_H
