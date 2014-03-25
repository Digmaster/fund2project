#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Components/ComponentBase.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
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
        virtual sf::Drawable* getDrawable() {}
        virtual void go(sf::Time) {}
    protected:
        static TextureManager texMan;
    private:
};

#endif // RENDERCOMPONENT_H
