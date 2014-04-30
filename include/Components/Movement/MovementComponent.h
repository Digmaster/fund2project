#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "Components/ComponentBase.h"
#include <string>

enum MoveState : int {
    onGround,
    leftWalk,
    rightWalk,
    attack,
    jumping,
    onLadder,
    ladderLeft,
    ladderRight,
    ladderUp,
    ladderDown,
    inAir
};

///Takes an input component and moves/modifies other components based on it
class MovementComponent : public ComponentBase
{
    public:
        MovementComponent();
        MovementComponent(unsigned int ID);
        virtual ~MovementComponent();
        ///Returns the MoveState enum corresponding to the current state
        MoveState getState() {return currState;}
        ///Returns if the state has changed for precisely one frame
        bool hasChanged() {return changed;}
    protected:
        MoveState currState;
        MoveState nextState;
        bool changed;
    private:
};

#endif // MOVEMENTCOMPONENT_H
