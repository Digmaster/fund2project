#ifndef ANIMATEDCOMPONENT_H
#define ANIMATEDCOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "Rendering/AnimatedSprite.h"

///Simple abstract class for animated components
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
        sf::Drawable* getDrawable();
    protected:
    private:
};

#endif // ANIMATEDCOMPONENT_H
