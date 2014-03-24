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
        void setPosition(sf::Vector2f input, bool awaken = true);
        void move(sf::Vector2f input) {position+=input;};
        sf::Vector2f getPosition() {return position;}
        void setRotation(float input) {rotation = input;}
        float getRotation() {return rotation;}
    protected:
    private:
        sf::Vector2f position;
        float rotation;
};

#endif // WORLDPOSITIONCOMPONENT_H
