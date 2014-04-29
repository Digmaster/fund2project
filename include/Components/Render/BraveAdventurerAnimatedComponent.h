#ifndef BRAVEADVENTURERANIMATEDCOMPONENT_H
#define BRAVEADVENTURERANIMATEDCOMPONENT_H

#include "Components/Render/AnimatedComponent.h"

///Draws an animated component by looking at the movement component and a bit from input
class BraveAdventurerAnimatedComponent : public AnimatedComponent
{
    public:
        BraveAdventurerAnimatedComponent();
        BraveAdventurerAnimatedComponent(unsigned int id) : AnimatedComponent(id) {}
        void go(sf::Time fps);
    protected:
    private:
        int currDir;
};

#endif // BRAVEADVENTURERANIMATEDCOMPONENT_H
