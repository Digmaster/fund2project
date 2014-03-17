#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <SFML/System/Time.hpp>
#include "Components/ComponentBase.h"

class InputComponent : public ComponentBase {
    public:
        InputComponent();
        InputComponent(unsigned int ID) : ComponentBase(ID) {}
        virtual ~InputComponent();
        virtual void go(sf::Time) {}
    protected:
    private:
};

#endif // INPUTCOMPONENT_H
