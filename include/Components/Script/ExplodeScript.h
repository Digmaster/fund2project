#ifndef EXPLODESCRIPT_H
#define EXPLODESCRIPT_H

#include <ScriptComponent.h>

#include <Box2D/Box2D.h>
#include <SFML/System/Vector2.hpp>


class ExplodeScript : public ScriptComponent
{
    public:
        ExplodeScript();
        virtual ~ExplodeScript();

        virtual void go(sf::Time frameTime, Entity* entity) {} //does nothing

        ComponentBase::listenerList getListeners();
        void HandleMessage(Events event, EventObj* message, Entity* entity);
        static void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);
    protected:
    private:
        static void particalExplosion(sf::Vector2f location, float power);
        static void raycastExplosion(sf::Vector2f location, float blastRadius, float power, std::shared_ptr<IDComponent> identification);

        static int numRays;
        static float DEGTORAD;
        static int pixelsPerMeter;
};

class RaycastObjectFound : public b2RayCastCallback
{
public:
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
    b2Vec2 center;
    float power;
    int numRays;
    std::shared_ptr<IDComponent> faction;
};

#endif // EXPLODESCRIPT_H
