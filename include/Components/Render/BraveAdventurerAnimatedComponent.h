#ifndef BRAVEADVENTURERANIMATEDCOMPONENT_H
#define BRAVEADVENTURERANIMATEDCOMPONENT_H

#include "Components/Render/AnimatedComponent.h"
#include "Components/EventDefines.h"
#include <unordered_map>

///Draws an animated component by looking at the movement component and a bit from input
class BraveAdventurerAnimatedComponent : public AnimatedComponent
{
    public:
        BraveAdventurerAnimatedComponent();
        void go(sf::Time fps, Entity* entity);
        listenerList getListeners();
        void HandleMovementChange(Events event, EventObj* message, Entity* entity);
    protected:
    private:
        int currDir;
        sf::Time _healthCooldown;

        std::unordered_map<int, sf::Time> cooldowns;
        std::vector<bool> cooldownValues;

        static const int getNumCooldowns() {return 1;}
        enum Cooldowns : int {
            HURT
        };

        static const sf::Time getHealthCooldown() { return sf::seconds(.5); }
        static const sf::Color getHealthHurtColor() { return sf::Color::Red; }
};

#endif // BRAVEADVENTURERANIMATEDCOMPONENT_H
