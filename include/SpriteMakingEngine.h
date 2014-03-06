#ifndef SPRITEMAKINGENGINE_H
#define SPRITEMAKINGENGINE_H

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include <iostream>
#include <fstream>
#include <string>
#include "TextureManager.h"
#include "SpriteManager.h"
#include "RenderEngine.h"
#include "SpriteSheet.h"

class SpriteMakingEngine
{
    public:
        /** Default constructor */
        SpriteMakingEngine();
        /** Default destructor */
        ~SpriteMakingEngine();
        void run();
        RenderEngine rendEng;
    protected:
    private:
};

#endif // SPRITEMAKINGENGINE_H
