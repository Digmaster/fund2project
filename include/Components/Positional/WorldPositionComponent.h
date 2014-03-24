#ifndef WORLDPOSITIONCOMPONENT_H
#define WORLDPOSITIONCOMPONENT_H

#include "Components/ComponentBase.h"
#include <SFML/System/Vector2.hpp>

class WorldPositionComponent : public ComponentBase {
    public:
        /** Default constructor */
        WorldPositionComponent() {}
        WorldPositionComponent(unsigned int ID);
        /** Default destructor */
        void go(sf::Time frameTime);
        void setPosition(sf::Vector2f input);
        void move(sf::Vector2f input) {position+=input;};
        sf::Vector2f getPosition() {return position;}
    protected:
    private:
        sf::Vector2f position;
};

#endif // WORLDPOSITIONCOMPONENT_H
