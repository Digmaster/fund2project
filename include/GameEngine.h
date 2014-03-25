#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class RenderEngine;
class PhysicsEngine;

class GameEngine
{
    public:
        /** Default constructor */
        GameEngine();
        /** Default destructor */
        ~GameEngine();
        void go();
        RenderEngine* rendEng;
        PhysicsEngine* physEng;
    protected:
    private:
        void init();
        void gameLoop();
};

#endif // GAMEENGINE_H
