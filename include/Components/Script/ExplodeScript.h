#ifndef EXPLODESCRIPT_H
#define EXPLODESCRIPT_H

#include <ScriptComponent.h>


class ExplodeScript : public ScriptComponent
{
    public:
        ExplodeScript();
        virtual ~ExplodeScript();

        virtual void go(sf::Time frameTime, Entity* entity) {} //does nothing

        ComponentBase::listenerList getListeners();
        void HandleMessage(Events event, EventObj* message, Entity* entity);
    protected:
    private:
};

#endif // EXPLODESCRIPT_H
