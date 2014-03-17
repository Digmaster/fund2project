#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Rendering/RenderEngine.h"
#include "Components/ComponentManager.h"

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
