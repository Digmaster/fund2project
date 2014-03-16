#ifndef WORLDPOSITIONCOMPONENT_H
#define WORLDPOSITIONCOMPONENT_H

#include "ComponentBase.h"
#include <SFML/System/Vector2.hpp>

class WorldPositionComponent : public ComponentBase {
    public:
        /** Default constructor */
        WorldPositionComponent();
        /** Default destructor */
        void go(sf::Time frameTime);
        void setPosition(sf::Vector2f input) {position = input;}
        sf::Vector2f getPosition() {return position;}
    protected:
    private:
        sf::Vector2f position;
};

#endif // WORLDPOSITIONCOMPONENT_H
