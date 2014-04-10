#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "Components/ComponentBase.h"
#include <string>

enum MoveState : int {
    onGround,
    jumping,
    onLadder,
    inAir,
};

class MovementComponent : public ComponentBase
{
    public:
        MovementComponent();
        MovementComponent(unsigned int ID);
        virtual ~MovementComponent();
        MoveState getState() {return currState;}
    protected:
        MoveState currState;
        MoveState nextState;
    private:
};

#endif // MOVEMENTCOMPONENT_H
