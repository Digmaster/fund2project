#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Components/ComponentBase.h"
#include "Rendering/RenderEngine.h"
#include <SFML/System/Time.hpp>
#include <iostream>
#include "Rendering/TextureManager.h"

class RenderEngine;

class RenderComponent : public ComponentBase
{
    public:
        /** Default constructor */
        RenderComponent();
        RenderComponent(unsigned int ID);
        /** Default destructor */
        virtual ~RenderComponent();
        static void setRenderEngine(RenderEngine* input) {rendEng = input;}
        virtual void go(sf::Time) {}
    protected:
        static RenderEngine* rendEng;
        static TextureManager texMan;
    private:
};

#endif // RENDERCOMPONENT_H
