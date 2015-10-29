#ifndef TARGETCOMPONENT_H
#define TARGETCOMPONENT_H

#include "Components/ComponentBase.h"

///contains the ID of a target for scripts
class TargetComponent : public ComponentBase
{
    public:
        TargetComponent(unsigned int);
        TargetComponent(std::string);
        ~TargetComponent();
        void setTarget(unsigned int id) {targetID = id;}
        void setTarget(std::string);
        unsigned int getTarget() {return targetID;}
        virtual void go(sf::Time frameTime, Entity* entity);
    protected:
    private:
        unsigned int targetID;
        std::string name;
};

#endif // TARGETCOMPONENT_H
