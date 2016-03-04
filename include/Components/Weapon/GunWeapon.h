#ifndef GUNWEAPON_H
#define GUNWEAPON_H

#include <WeaponComponent.h>


class GunWeapon : public WeaponComponent
{
    public:
        GunWeapon(int damage = 2, sf::Time cooldown = sf::seconds(.1));

        void fire(float angle, Entity* entity);

    protected:
        int damage;
    private:
};

#endif // GUNWEAPON_H
