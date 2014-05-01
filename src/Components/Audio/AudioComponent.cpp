#include "Components/Audio/AudioComponent.h"
#include <SFML/Audio.hpp>
#include "Components/ComponentManager.h"
#include "InputEngine.h"
#include "GameEngine.h"
#include <string>

AudioComponent::AudioComponent()
{
    //ctor
}

AudioComponent::AudioComponent(unsigned int ID) : ComponentBase(ID){
    compMan->audioSym.addComponent(this);
    buffer1.loadFromFile("assets/sound/Running.wav");
    buffer2.loadFromFile("assets/sound/jump.wav");
    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound1.setLoop(true);
    sound2.setLoop(true);
}

AudioComponent::~AudioComponent()
{
    //dtor
}

//Looped function for audio instances
void AudioComponent::go(sf::Time){
    MovementComponent* action=ComponentManager::getInst().moveSym.getComponent(getID());
    //std::cout<<action->getState()<<std::endl;
    if(action) {
        //Play sound for walking/running
        if(action->getState()==1 || action->getState()==2){
            sound1.setVolume(50);
            //only play if sound not already playing
            if(sound1.getStatus()!=sf::SoundSource::Status::Playing)
                sound1.play();
                sound2.stop();
        }

        //Play sound for jumping/spinning
        else if (action->getState()==10){
            sound2.setVolume(30);
            //only play if sound not already playing
            if(sound2.getStatus()!=sf::SoundSource::Status::Playing)
                sound2.play();
                sound1.stop();
        }
        else{
            //if no actions require sound, play no sound
            sound1.stop();
            sound2.stop();
        }
    }
}
