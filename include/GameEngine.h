#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Rendering/RenderEngine.h"
#include "Components/ComponentManager.h"
#include "physics/PhysicsEngine.h"

class GameEngine
{
    public:
        /** Default constructor */
        GameEngine();
        /** Default destructor */
        ~GameEngine();
        void go();
        RenderEngine rendEng;
        PhysicsEngine physEng;
    protected:
    private:
        void init();
        void gameLoop();
};

#endif // GAMEENGINE_H
