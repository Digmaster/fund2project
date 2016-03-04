#ifndef MISSILEWEAPON_H
#define MISSILEWEAPON_H

#include <WeaponComponent.h>


class MissileWeapon : public WeaponComponent
{
    public:
        MissileWeapon(int damage = 10, sf::Time cooldown = sf::seconds(.5));

        void fire(float angle, Entity* entity);
    protected:
    private:
        int damage;
};

#endif // MISSILEWEAPON_H
