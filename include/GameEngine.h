#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "RenderEngine.h"
#include "ComponentManager.h"

class GameEngine
{
    public:
        /** Default constructor */
        GameEngine();
        /** Default destructor */
        ~GameEngine();
        void go();
        RenderEngine rendEng;
        //EntityList entList;
        //CommandQueve commQueve;
    protected:
    private:
        void init();
        void gameLoop();
};

#endif // GAMEENGINE_H
