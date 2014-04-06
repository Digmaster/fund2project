#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class RenderEngine;
class PhysicsEngine;
class InputEngine;
//! The overruling class which encapsolates all nessesary objects for the game.
/*! GameEngine should be created at the beginning of any game. This contains pointers to all nesessary engines. Passing a pointer to the game engine to something allows it
to have access to effectively all data in the program.
*/
class GameEngine
{
    public:
        /*! Default constructor */
        GameEngine();
        /*! Default destructor */
        ~GameEngine();
        //! Starts the game engine.
        /*! Until the rendering window is closed (or exception throw), this function will continue to loop */
        void go();
        //! Pauses the game
        /*! When paused the game will only update InputEngine, as that's when unpaused should be called */
        void pause() {paused=true;}
        //! Unpauses the game
        void unpause() {paused=false;}
        //! Rendering Engine Pointer
        /*! This should be the only graphics engine instance created
            /see RenderEngine */
        RenderEngine* rendEng;
        //! Physics Engine Pointer
        /*! This should be the only physics engine instance created
            /see RenderEngine */
        PhysicsEngine* physEng;
        //! Input Engine pointer
        /*! This should be the only physics engine instance created
        /see InputEngine */
        InputEngine* inputEng;
    protected:
    private:
        void init();
        void gameLoop();
        bool paused;
};

#endif // GAMEENGINE_H
