#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class RenderEngine;
class PhysicsEngine;
class InputEngine;

class GameEngine
{
    public:
        /** Default constructor */
        GameEngine();
        /** Default destructor */
        ~GameEngine();
        void go();
        void pause() {paused=true;}
        void unpause() {paused=false;}
        RenderEngine* rendEng;
        PhysicsEngine* physEng;
        InputEngine* inputEng;
    protected:
    private:
        void init();
        void gameLoop();
        bool paused;
};

#endif // GAMEENGINE_H
