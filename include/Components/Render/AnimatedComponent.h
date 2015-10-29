#ifndef ANIMATEDCOMPONENT_H
#define ANIMATEDCOMPONENT_H

#include "Components/Render/RenderComponent.h"
#include "Rendering/AnimatedSprite.h"

///Simple abstract class for animated components
class AnimatedComponent : public RenderComponent
{
    public:
        AnimatedComponent() : RenderComponent() {}
        /** Default destructor */
        virtual ~AnimatedComponent();
        virtual void go(sf::Time, Entity* entity);
        void setSprite(AnimatedSprite input);
        AnimatedSprite sprite;
        sf::Drawable* getDrawable();
    protected:
    private:
};

#endif // ANIMATEDCOMPONENT_H
