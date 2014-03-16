#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include "RenderComponent.h"
#include "WorldPositionComponent.h"
#include "ComponentSystem.h"

class ComponentManager
{
    public:
        /** Default destructor */
        virtual ~ComponentManager();

        ComponentSystem<ComponentBase> etcSym;
        ComponentSystem<RenderComponent> rendSym;
        ComponentSystem<WorldPositionComponent> posSym;
        static unsigned int getNewID();

        static ComponentManager& getInst() {
            static ComponentManager INSTANCE;
            return INSTANCE;
        }
    protected:
    private:

};

#endif // COMPONENTMANAGER_H
