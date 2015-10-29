#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "Components/Input/InputComponent.h"

///Simply grabs the appropriate input information from the Input Engine
class KeyboardInput : public InputComponent
{
    public:
        KeyboardInput();
        virtual ~KeyboardInput();
        void go(sf::Time, Entity* entity);
    protected:
    private:
};

#endif // KEYBOARDINPUT_H
