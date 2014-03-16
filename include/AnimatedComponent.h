#ifndef ANIMATEDCOMPONENT_H
#define ANIMATEDCOMPONENT_H

#include "RenderComponent.h"
#include "AnimatedSprite.h"


class AnimatedComponent : RenderComponent
{
    public:
        /** Default constructor */
        AnimatedComponent();
        /** Default destructor */
        virtual ~AnimatedComponent();
        void go(sf::Time frameTime);
    protected:
    private:
        AnimatedSprite sprite;
};

#endif // ANIMATEDCOMPONENT_H
