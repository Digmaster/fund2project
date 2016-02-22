#ifndef TELEPORTSCRIPT_H
#define TELEPORTSCRIPT_H

#include <Components/Script/ScriptComponent.h>


class TeleportScript : public ScriptComponent
{
    public:
        TeleportScript();
        virtual ~TeleportScript();

        virtual void go(sf::Time frameTime, Entity* entity);

        ComponentBase::listenerList getListeners();
        void HandleMessage(Events event, EventObj* message, Entity* entity);
    protected:
    private:
};

#endif // TELEPORTSCRIPT_H
