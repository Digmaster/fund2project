#ifndef TELEPORTSCRIPT_H
#define TELEPORTSCRIPT_H

#include <Components/Script/ScriptComponent.h>
#include <Box2D/Box2D.h>


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

class HovercarRayCastClosestCallback : public b2RayCastCallback
{
public:
    HovercarRayCastClosestCallback()
    {
        m_hit = false;
    }

    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
    {
        m_hit = true;
        m_point = point;
        return fraction;
    }

    bool m_hit;
    b2Vec2 m_point;
};

#endif // TELEPORTSCRIPT_H
