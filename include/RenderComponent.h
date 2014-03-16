#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "ComponentBase.h"
#include <SFML/System/Time.hpp>

class RenderComponent : public ComponentBase
{
    public:
        /** Default constructor */
        RenderComponent();
        /** Default destructor */
        virtual ~RenderComponent();
    protected:
    private:
};

#endif // RENDERCOMPONENT_H
