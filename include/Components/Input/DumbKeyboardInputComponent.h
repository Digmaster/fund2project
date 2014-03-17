#ifndef DUMBKEYBOARDINPUTCOMPONENT_H
#define DUMBKEYBOARDINPUTCOMPONENT_H

#include "Components/Input/InputComponent.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Components/Positional/WorldPositionComponent.h"


class DumbKeyboardInputComponent : public InputComponent
{
    public:
        DumbKeyboardInputComponent();
        DumbKeyboardInputComponent(unsigned int ID) : InputComponent(ID) {}
        void go(sf::Time);
    protected:
    private:
};

#endif // DUMBKEYBOARDINPUTCOMPONENT_H
