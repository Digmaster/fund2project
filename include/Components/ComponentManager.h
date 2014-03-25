#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
class RenderComponent;
class WorldPositionComponent;
class InputComponent;
class MovementComponent;
class PhysicsComponent;

#include "Components/ComponentSystem.h"

class ComponentManager
{
    public:
        /** Default destructor */
        virtual ~ComponentManager();

        ComponentSystem<ComponentBase*> etcSym;
        void processAll(sf::Time frameTime);
        ComponentSystem<RenderComponent*> rendSym;
        ComponentSystem<WorldPositionComponent*> posSym;
        ComponentSystem<InputComponent*> inputSym;
        ComponentSystem<MovementComponent*> moveSym;
        ComponentSystem<PhysicsComponent*> physSym;
        static unsigned int getNewID();

        static ComponentManager& getInst() {
            static ComponentManager INSTANCE;
            return INSTANCE;
        }
    protected:
    private:

};

#endif // COMPONENTMANAGER_H
