#ifndef ANIMATIONHOLDER_H
#define ANIMATIONHOLDER_H

// Basically a dump sprite, used in SpriteMaker

#include <string>
#include <map>
#include "Animation.h"

class AnimationHolder
{
    public:
        /** Default constructor */
        AnimationHolder();
        /** Default destructor */
        virtual ~AnimationHolder();
        void addAnimation(std::string name, Animation ani) { animations[name] = ani;}
        Animation& getAnimation(std::string);
        int getNumAnimations();
    protected:
    private:
        std::map<std::string, Animation> animations;
};

#endif // ANIMATIONHOLDER_H
