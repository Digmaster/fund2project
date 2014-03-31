#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "Components/Input/InputComponent.h"


class KeyboardInput : public InputComponent
{
    public:
        KeyboardInput() : InputComponent() {}
        KeyboardInput(unsigned int ID);
        virtual ~KeyboardInput();
        void go(sf::Time);
    protected:
    private:
};

#endif // KEYBOARDINPUT_H
