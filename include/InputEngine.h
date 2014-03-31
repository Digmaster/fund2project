#ifndef INPUTENGINE_H
#define INPUTENGINE_H
#include <SFML/Graphics.hpp>

class GameEngine;

class InputEngine
{
    public:
        InputEngine();
        ~InputEngine();
        void update(GameEngine*);
        bool getWalkLeft() { return walkLeft; }
        bool getWalkRight() { return walkRight; }
        bool getClimbUp() { return climbUp; }
        bool getClimbDown() { return climbDown; }
        bool getActivate() { return activate; }
        bool getFire() { return fire; }
        bool getJump() { return jump; }
        int getMouseX() { return mouseX; }
        int getMouseY() { return mouseY; }
        float getMouseAngle(sf::Vector2f);
    protected:
    private:
        bool walkLeft;
        bool walkRight;
        bool climbUp;
        bool climbDown;
        bool activate;
        bool fire;
        bool jump;
        int mouseX;
        int mouseY;
};

#endif // INPUTENGINE_H
