#ifndef BASICAIINPUT_H
#define BASICAIINPUT_H

#include "Components/Input/InputComponent.h"

class BasicAIInput : public InputComponent
{
    public:
        BasicAIInput();
        virtual ~BasicAIInput();

        virtual void go(sf::Time, Entity* entity);

    protected:
    private:
        sf::Time walkTimer;
        bool gotoLeft;
};

#endif // BASICAIINPUT_H
