#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
class RenderComponent;
class WorldPositionComponent;
class InputComponent;
class MovementComponent;
class PhysicsComponent;
class IDComponent;
class ScriptComponent;
class TargetComponent;
class AudioComponent;
class StatsComponent;

#include "Components/ComponentSystem.h"

///Manages/contains all components
class ComponentManager
{
    public:
        /** Default destructor */
        virtual ~ComponentManager();


        void processAll(sf::Time frameTime);
         ComponentSystem<ComponentBase*> etcSym;
        ComponentSystem<RenderComponent*> rendSym;
        ComponentSystem<WorldPositionComponent*> posSym;
        ComponentSystem<InputComponent*> inputSym;
        ComponentSystem<MovementComponent*> moveSym;
        ComponentSystem<PhysicsComponent*> physSym;
        ComponentSystem<IDComponent*> idSym;
        ComponentSystem<TargetComponent*> targetSym;
        ComponentSystem<ScriptComponent*> scriptSym;
        ComponentSystem<AudioComponent*> audioSym;
        ComponentSystem<StatsComponent*> statSym;
        static unsigned int getNewID();

        static ComponentManager& getInst() {
            static ComponentManager INSTANCE;
            return INSTANCE;
        }

        unsigned int name2ID(std::string);
    protected:
    private:

};

#endif // COMPONENTMANAGER_H
