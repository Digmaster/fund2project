#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "Components/ComponentBase.h"


class ScriptComponent : public ComponentBase
{
    public:
        ScriptComponent() : ComponentBase() {}
        ScriptComponent(unsigned int ID);
        virtual ~ScriptComponent();
        virtual bool isActive() {return active;}
        virtual bool enable() {active = true;}
        virtual bool disable() {active = false;}
    protected:
        bool active;
    private:
};

#endif // SCRIPTCOMPONENT_H
