#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include <SFML/Audio.hpp>
#include "Components/ComponentBase.h"
#include "Components/EventDefines.h"

///Super simple audio component which plays audio based on movement
class AudioComponent : public ComponentBase
{
    public:
        /*! Default Constructor */
        AudioComponent();
        /*! Default Destructor */
        virtual ~AudioComponent();
        ///function runs until program end
        void go(sf::Time, Entity* entity);

        listenerList getListeners();

    protected:
    private:
        sf::Sound sound1; //Walking sound
        sf::Sound sound2; //Jumping sound
        sf::Sound sound3;

        void HandleMovementChange(Events event, EventObj*, Entity* entity);
};

#endif // AUDIOCOMPONENT_H
