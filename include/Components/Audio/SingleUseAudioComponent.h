#ifndef SINGLEUSEAUDIOCOMPONENT_H
#define SINGLEUSEAUDIOCOMPONENT_H

#include <AudioComponent.h>


class SingleUseAudioComponent : public AudioComponent
{
    public:
        SingleUseAudioComponent(std::string sound, bool DestroyOnFinish = true);
        virtual ~SingleUseAudioComponent();

        void go(sf::Time, Entity* entity);
    protected:
    private:
        sf::Sound sound;
        sf::SoundBuffer buffer; //walking soundbuffer
};

#endif // SINGLEUSEAUDIOCOMPONENT_H
