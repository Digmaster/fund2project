#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H

#include <Components/ComponentBase.h>


class WeaponComponent : public ComponentBase
{
    public:
        WeaponComponent();

        virtual void go(sf::Time frameTime,  Entity* entity);

        bool canFire() { return fireTimer <= sf::Time::Zero && (currClip > 0 || currClip == -1); }

        virtual void fire(float angle, Entity* entity) = 0;

    protected:
        int clipSize;
        int maxAmmo;
        int currClip;
        int currAmmo;

        sf::Time fireTimer;
        sf::Time initalFireTimer;
    private:
};

#endif // WEAPONCOMPONENT_H
