#ifndef SPRITEHOLDER_H
#define SPRITEHOLDER_H

#include <unordered_map>
#include <string>
#include "AnimatedSprite.h"

class SpriteHolder
{
    public:
        /** Default constructor */
        SpriteHolder();
        /** Default destructor */
        virtual ~SpriteHolder();
    protected:
    private:
        unordered_map<std::string, Animation> animationHolder;
};

#endif // SPRITEHOLDER_H
