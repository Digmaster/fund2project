#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SFML/System/Time.hpp>
#include "Components/ComponentBase.h"

class InputComponent : public ComponentBase {
    public:
        InputComponent();
        InputComponent(unsigned int ID);
        virtual ~InputComponent();
        virtual void go(sf::Time) {}
        bool walkLeft;
        bool walkRight;
        bool climbUp;
        bool climbDown;
        bool fire;
        bool jump;
        bool activate;
        int currWeapon;
        float fireDir;
        float mouseX;
        float mouseY;
    protected:
    private:
};

#endif // INPUTCOMPONENT_H
