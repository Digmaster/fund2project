#pragma once

#include <deque>
#include "AnimatedSprite.h"
#include "RenderEngine.h"
class AnimatedSprite;

class RenderList {
    friend class RenderEngine;
    public:
        /** Default constructor */
        RenderList();
        /** Default destructor */
        ~RenderList();
        void addSprite(AnimatedSprite* input) {renderList.push_back(input);}
        void flush() {renderList.clear();}
    protected:
    private:
        deque<AnimatedSprite*> renderList;
};
