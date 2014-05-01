#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H

#include "Components/ComponentBase.h"


class StatsComponent : public ComponentBase
{
    public:
        /** Default constructor */
        StatsComponent();
        StatsComponent(unsigned int ID, int health = 100);
        /** Default destructor */
        virtual ~StatsComponent();
        virtual void go(sf::Time frameTime);
        int getHealth();
        void setHealth(int);
        void modHealth(int);
        bool isDead();
    protected:
    private:
        int health;
        bool dead;
};

#endif // STATSCOMPONENT_H
