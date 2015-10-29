#ifndef BRAVEADVENTURERANIMATEDCOMPONENT_H
#define BRAVEADVENTURERANIMATEDCOMPONENT_H

#include "Components/Render/AnimatedComponent.h"

///Draws an animated component by looking at the movement component and a bit from input
class BraveAdventurerAnimatedComponent : public AnimatedComponent
{
    public:
        BraveAdventurerAnimatedComponent();
        void go(sf::Time fps, Entity* entity);
    protected:
    private:
        int currDir;
};

#endif // BRAVEADVENTURERANIMATEDCOMPONENT_H
