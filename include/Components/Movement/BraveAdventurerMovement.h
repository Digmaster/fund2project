#ifndef BRAVEADVENTURERMOVEMENT_H
#define BRAVEADVENTURERMOVEMENT_H

#include "Components/Movement/MovementComponent.h"

#include <vector>

class WeaponComponent;

///Simple movement file which takes any input and translates it into movement; nothing more complicated than running back and forth and whatnot.
class BraveAdventurerMovement : public MovementComponent
{
    public:
        BraveAdventurerMovement();
        ~BraveAdventurerMovement() {}
        void go(sf::Time frameTime, Entity* entity);
    protected:
    private:
        sf::Time jumpTimer;
        sf::Time fireTimer;

        std::vector<std::shared_ptr<WeaponComponent>> availableWeapons;
        std::shared_ptr<WeaponComponent> currWeapon;
};

#endif // BRAVEADVENTURERMOVEMENT_H
