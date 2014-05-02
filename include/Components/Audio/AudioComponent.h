#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include <SFML/Audio.hpp>
#include "Components/ComponentBase.h"

///Super simple audio component which plays audio based on movement
class AudioComponent : public ComponentBase
{
    public:
        /*! Default Constructor */
        AudioComponent();
        AudioComponent(unsigned int ID);
        /*! Default Destructor */
        virtual ~AudioComponent();
        ///function runs until program end
        void go(sf::Time);
    protected:
    private:
        sf::Sound sound1; //Walking sound
        sf::Sound sound2; //Jumping sound
        sf::Sound sound3;
        sf::SoundBuffer buffer1; //walking soundbuffer
        sf::SoundBuffer buffer2; //jumping soundbuffer
        sf::SoundBuffer buffer3;
};

#endif // AUDIOCOMPONENT_H
