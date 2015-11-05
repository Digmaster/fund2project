#ifndef ENTITY_H
#define ENTITY_H

#include<list>
#include<unordered_map>
#include<memory>
#include<typeindex>
#include<vector>
#include<functional>
#include <sstream>

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
        void setAudio(AudioComponent* a);
        AudioComponent* getAudio();

        void setRender(RenderComponent* a);
        RenderComponent* getRender();

        void setIdentification(IDComponent* a);
        IDComponent* getIdentification();

        void setInput(InputComponent* a);
        InputComponent* getInput();

        void setMovement(MovementComponent* a);
        MovementComponent* getMovement();

        void setPhysics(PhysicsComponent* a);
        PhysicsComponent* getPhysics();

        void setPosition(WorldPositionComponent* a);
        WorldPositionComponent* getPosition();

        void setStats(StatsComponent* a);
        StatsComponent* getStats();

        void setTarget(TargetComponent* a);
        TargetComponent* getTarget();

        void addScript(ScriptComponent* s)      {scripts.push_back(s);}
        void removeScript(ScriptComponent* s)   {scripts.remove(s);}
        std::list<ScriptComponent*> getScripts() {return scripts;}

        int getID() {return _ID;}

        //Deferred Delete logic
        void setDelete() {_delete = true;}
        int isDeleted() {return _delete;}

        // Listener Logic
        typedef std::function<void(Events, EventObj*, Entity*)> listener;
        typedef std::function<void(ComponentBase&, Events, EventObj*, Entity*)> unboundListener;

        void addListener(std::type_index toListenTo, listener toCall);
        //void addListener(std::type_index toListenTo, ComponentBase* obj, unboundListener toCall);
        void removeListener(std::type_index toListenTo, listener toCall);
        void callListeners(std::type_index origin, Events event, EventObj* = nullptr);
    protected:
        int _ID;
        bool _delete;

        AudioComponent* audio;
        RenderComponent* render;
        IDComponent* identification;
        InputComponent* input;
        MovementComponent* movement;
        PhysicsComponent* physics;
        WorldPositionComponent* position;
        StatsComponent* stats;
        TargetComponent* target;
    private:
        std::list<ScriptComponent*> scripts;
        std::unordered_map<std::type_index, std::list<listener> > componentListeners;
};

#endif // ENTITY_H
