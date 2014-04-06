#ifndef INPUTENGINE_H
#define INPUTENGINE_H
#include <SFML/Graphics.hpp>

class GameEngine;

//! Manages input to the window and provides a common interface to see the current input
/*! Input will only be parsed when the window is active, although this class should be called every frame even when the GameEngine is paused, as this is the only way to unpause it. */
class InputEngine
{
    public:
        //! Default constructor
        InputEngine();
        //! Default destructor
        ~InputEngine();
        //! Updates all input and provides basic processing of it.
        /*! Iterates through the window event deque and process input such as window resize, focus lost/gained (to pause/unpause the GameEngine
            \param GameEngine* Pointer to the instantiated GameEngine, used for access to RenderEngine
        */
        void update(GameEngine*);
        //! Returns the status of the button mapped to WalkLeft
        /*! (Default: A) */
        bool getWalkLeft() { return walkLeft; }
        //! Returns the status of the button mapped to WalkRight
        /*! (Default: D) */
        bool getWalkRight() { return walkRight; }
        //! Returns the status of the button mapped to ClimbUp
        /*! (Default: W) */
        bool getClimbUp() { return climbUp; }
        //! Returns the status of the button mapped to ClimbDown
        /*! (Default: S) */
        bool getClimbDown() { return climbDown; }
        //! Returns the status of the button mapped to ACtivate
        /*! (Default: E) */
        bool getActivate() { return activate; }
        //! Returns the status of the mouse button mapped to Fire
        /*! (Default: LeftMouseButton) */
        bool getFire() { return fire; }
        //! Returns the status of the button mapped to Jump
        /*! (Default: Spacebar) */
        bool getJump() { return jump; }
        //! Returns the position of the mouse, relative to the GameWorld
        sf::Vector2f getMousePos() {return mousePos;}
        //! Returns the position of the mouse, relative to the Window
        sf::Vector2f getScreenMousePos() {return srcMousePos;}
        //! Returns the angle of the courser relative to the position
        /*! Uses the Mouse Position, no method exists for a position relative to the window
            \param sf::Vector2f position to find angle relative to
            \return the angle, in degrees */
        float getMouseAngle(sf::Vector2f);
    protected:
    private:
        GameEngine* eng;
        bool walkLeft;
        bool walkRight;
        bool climbUp;
        bool climbDown;
        bool activate;
        bool fire;
        bool jump;
        sf::Vector2i scrMousePos;
        sf::Vector2f mousePos;
};

#endif // INPUTENGINE_H
