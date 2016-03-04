#ifndef ENTITY_H
#define ENTITY_H

#include<list>
#include<map>
#include<memory>
#include<typeindex>
#include<vector>
#include<functional>
#include <sstream>
#include <SFML/System/Time.hpp>

#include "Components/EventDefines.h"
//#include "Components/Script/ScriptComponent.h"

class AudioComponent;
class RenderComponent;
class IDComponent;
class InputComponent;
class MovementComponent;
class PhysicsComponent;
class WorldPositionComponent;
class StatsComponent;
class TargetComponent;
class ComponentBase;
class ScriptComponent;
class WeaponComponent;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

/// Contains all the components an entity has
class Entity
{
    public:
        //Constructors and Destructors
        Entity(int ID);
        virtual ~Entity();

        //Component Management
        template<typename T>
        void setComponent(T* o, T n);

        void update(sf::Time frameTime);

        void setAudio(std::shared_ptr<AudioComponent> a);
        std::shared_ptr<AudioComponent> getAudio();

        void setRender(std::shared_ptr<RenderComponent> a);
        std::shared_ptr<RenderComponent> getRender();

        void setIdentification(std::shared_ptr<IDComponent> a);
        std::shared_ptr<IDComponent> getIdentification();

        void setInput(std::shared_ptr<InputComponent> a);
        std::shared_ptr<InputComponent> getInput();

        void setMovement(std::shared_ptr<MovementComponent> a);
        std::shared_ptr<MovementComponent> getMovement();

        void setPhysics(std::shared_ptr<PhysicsComponent> a);
        std::shared_ptr<PhysicsComponent> getPhysics();

        void setPosition(std::shared_ptr<WorldPositionComponent> a);
        std::shared_ptr<WorldPositionComponent> getPosition();

        void setStats(std::shared_ptr<StatsComponent> a);
        std::shared_ptr<StatsComponent> getStats();

        void setTarget(std::shared_ptr<TargetComponent> a);
        std::shared_ptr<TargetComponent> getTarget();

        void setWeapon(std::shared_ptr<WeaponComponent> a);
        std::shared_ptr<WeaponComponent> getWeapon();

        void addScript(std::shared_ptr<ScriptComponent> s);
        void removeScript(std::shared_ptr<ScriptComponent> s);
        std::list<std::shared_ptr<ScriptComponent>> getScripts() {return scripts;}

        int getID() {return _ID;}

        //Deferred Delete logic
        void setDelete() {_delete = true;}
        int isDeleted() {return _delete;}

        // Listener Logic
        typedef std::function<void(Events, EventObj*, Entity*)> listener;
        typedef std::function<void(ComponentBase&, Events, EventObj*, Entity*)> unboundListener;

        typedef std::function<void()> deferredListenerCall;

        void addListener(Events toListenTo, listener& toCall);
        void removeListener(Events toListenTo, listener& toCall);

        /// Fires the listener message immediately
        void callListeners(Events event, EventObj* = nullptr);

        /// Fires the listener message on start of next "go"
        void callListenersDeferred(Events event, EventObj* = nullptr);
    protected:
        int _ID;
        bool _delete;

        std::shared_ptr<AudioComponent> audio;
        std::shared_ptr<RenderComponent> render;
        std::shared_ptr<IDComponent> identification;
        std::shared_ptr<InputComponent> input;
        std::shared_ptr<MovementComponent> movement;
        std::shared_ptr<PhysicsComponent> physics;
        std::shared_ptr<WorldPositionComponent> position;
        std::shared_ptr<StatsComponent> stats;
        std::shared_ptr<TargetComponent> target;
        std::shared_ptr<WeaponComponent> weapon;
    private:
        std::list<std::shared_ptr<ScriptComponent>> scripts;
        std::map<Events, std::list<listener> > componentListeners;
        std::list<deferredListenerCall> deferredCalls;
};

#endif // ENTITY_H
