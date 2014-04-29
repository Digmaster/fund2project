#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SFML/System/Time.hpp>
#include "Components/ComponentBase.h"

///Drives a Movement Component
class InputComponent : public ComponentBase {
    public:
        InputComponent();
        InputComponent(unsigned int ID);
        virtual ~InputComponent();
        virtual void go(sf::Time) {}
        ///Triggers a movement left
        bool walkLeft;
        ///Triggers a movement right
        bool walkRight;
        ///Triggers a movement up. Also starts climbing
        bool climbUp;
        ///triggers a movement down. Also starts climbing
        bool climbDown;
        ///Triggers a fire. PEW PEW PEW
        bool fire;
        ///Triggers a jump
        bool jump;
        ///Triggers an activate
        bool activate;
        ///Sets the current weapon (typically 0-9)
        int currWeapon;
        ///Indicates the direction, in degrees, to fire in
        float fireDir;
        ///Precise location of the mouse. Not typically used
        float mouseX;
        ///Precise location of the mouse. Not typically used
        float mouseY;
    protected:
    private:
};

#endif // INPUTCOMPONENT_H
