#ifndef BRAVEADVENTURERANIMATEDCOMPONENT_H
#define BRAVEADVENTURERANIMATEDCOMPONENT_H

#include "Components/Render/AnimatedComponent.h"


class BraveAdventurerAnimatedComponent : public AnimatedComponent
{
    public:
        BraveAdventurerAnimatedComponent();
        BraveAdventurerAnimatedComponent(unsigned int id) : AnimatedComponent(id) {}
        void go(sf::Time fps);
    protected:
    private:
};

#endif // BRAVEADVENTURERANIMATEDCOMPONENT_H
