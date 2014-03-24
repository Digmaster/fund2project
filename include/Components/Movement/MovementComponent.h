#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "Components/ComponentBase.h"
#include <string>

class MovementComponent : public ComponentBase
{
    public:
        MovementComponent();
        MovementComponent(unsigned int ID);
        virtual ~MovementComponent();
        std::string getCurrentMovement() {return currMovement;}
    protected:
        std::string currMovement;
    private:
};

#endif // MOVEMENTCOMPONENT_H
