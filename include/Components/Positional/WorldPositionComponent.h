#ifndef WORLDPOSITIONCOMPONENT_H
#define WORLDPOSITIONCOMPONENT_H

#include "Components/ComponentBase.h"
#include <SFML/System/Vector2.hpp>

class WorldPositionComponent : public ComponentBase {
    public:
        /** Default constructor */
        WorldPositionComponent() {}
        WorldPositionComponent(unsigned int ID, sf::Vector2f = sf::Vector2f(0,0), int = 0, float = 0);
        /** Default destructor */
        void go(sf::Time frameTime);
        void setPosition(sf::Vector2f input, bool awaken = true);
        void move(sf::Vector2f input, bool awaken = true);
        sf::Vector2f getPosition() {return position;}
        void setRotation(float input, bool awaken = true);
        float getRotation() {return rotation;}
        int getLayer();
        void setLayer(int);
    protected:
    private:
        sf::Vector2f position;
        float rotation;
        int layer;
        static int PPM;
};

#endif // WORLDPOSITIONCOMPONENT_H
