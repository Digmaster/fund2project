#ifndef TARGETCOMPONENT_H
#define TARGETCOMPONENT_H

#include "Components/ComponentBase.h"


class TargetComponent : public ComponentBase
{
    public:
        TargetComponent();
        TargetComponent(unsigned int, unsigned int);
        TargetComponent(unsigned int, std::string);
        ~TargetComponent();
        void setTarget(unsigned int id) {targetID = id;}
        void setTarget(std::string);
        unsigned int getTarget() {return targetID;}
    protected:
    private:
        unsigned int targetID;
};

#endif // TARGETCOMPONENT_H
