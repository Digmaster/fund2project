#ifndef ANIMATEDCOMPONENT_H
#define ANIMATEDCOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "Rendering/AnimatedSprite.h"


class AnimatedComponent : public RenderComponent
{
    public:
        /** Default constructor */
        AnimatedComponent();
        AnimatedComponent(unsigned int ID) : RenderComponent(ID) {}
        /** Default destructor */
        virtual ~AnimatedComponent();
        virtual void go(sf::Time);
        void setSprite(AnimatedSprite input) {sprite = input;}
        AnimatedSprite sprite;
    protected:
    private:
};

#endif // ANIMATEDCOMPONENT_H
