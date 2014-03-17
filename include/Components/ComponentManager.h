#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include "Components/Render/RenderComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Input/InputComponent.h"
#include "Components/Movement/MovementComponent.h"

#include "Components/ComponentSystem.h"

class ComponentManager
{
    public:
        /** Default destructor */
        virtual ~ComponentManager();

        ComponentSystem<ComponentBase> etcSym;
        void processAll(sf::Time frameTime);
        ComponentSystem<RenderComponent> rendSym;
        ComponentSystem<WorldPositionComponent> posSym;
        ComponentSystem<InputComponent> inputSym;
        ComponentSystem<MovementComponent> moveSym;
        static unsigned int getNewID();

        static ComponentManager& getInst() {
            static ComponentManager INSTANCE;
            return INSTANCE;
        }
    protected:
    private:

};

#endif // COMPONENTMANAGER_H
