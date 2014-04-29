#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include <SFML/Audio.hpp>
#include "Components/ComponentBase.h"

class AudioComponent : public ComponentBase
{
    public:
        AudioComponent();
        AudioComponent(unsigned int ID);
        virtual ~AudioComponent();
        void go(sf::Time);
    protected:
    private:
        sf::Sound sound1; //Walking sound
        sf::Sound sound2; //Jumping sound
        sf::SoundBuffer buffer1; //walking soundbuffer
        sf::SoundBuffer buffer2; //jumping soundbuffer
};

#endif // AUDIOCOMPONENT_H
