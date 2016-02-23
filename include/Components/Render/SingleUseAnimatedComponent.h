#ifndef SINGLEUSEANIMATEDCOMPONENT_H
#define SINGLEUSEANIMATEDCOMPONENT_H

#include <AnimatedComponent.h>


class SingleUseAnimatedComponent : public AnimatedComponent
{
    public:
        SingleUseAnimatedComponent() {}
        SingleUseAnimatedComponent(std::string sprite, std::string animation, bool DestroyOnFinish = true);

        void go(sf::Time fps, Entity* entity);
    protected:
    private:
};

#endif // SINGLEUSEANIMATEDCOMPONENT_H
