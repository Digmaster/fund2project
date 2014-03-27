#ifndef BRAVEADVENTURERINPUT_H
#define BRAVEADVENTURERINPUT_H

#include "Components/Input/InputComponent.h"


class BraveAdventurerInput : public InputComponent
{
    public:
        BraveAdventurerInput();
        BraveAdventurerInput(unsigned int ID) : InputComponent(ID) {}
        virtual ~BraveAdventurerInput();
        void go(sf::Time);
        void func();
    protected:
    private:
};

#endif // BRAVEADVENTURERINPUT_H
