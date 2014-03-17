#ifndef BRAVEADVENTURERMOVEMENT_H
#define BRAVEADVENTURERMOVEMENT_H

#include "Components/Movement/MovementComponent.h"

class BraveAdventurerMovement : public MovementComponent
{
    public:
        BraveAdventurerMovement();
        BraveAdventurerMovement(unsigned int ID) : MovementComponent(ID) {}
        ~BraveAdventurerMovement() {}
        void go(sf::Time frameTime);
        std::string getCurrentMovement();
    protected:
    private:
};

#endif // BRAVEADVENTURERMOVEMENT_H
