#include "Components/Audio/AudioComponent.h"
#include <SFML/Audio.hpp>
#include "Components/ComponentManager.h"
#include "Components/Movement/MovementComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "InputEngine.h"
#include "GameEngine.h"
#include "Components/Entity.h"
#include <string>
#include "Components/Stats/StatsComponent.h"

AudioComponent::AudioComponent() : ComponentBase(){
    buffer1.loadFromFile("assets/sound/Running.wav");
    buffer2.loadFromFile("assets/sound/jump.wav");
    buffer3.loadFromFile("assets/sound/death.wav");
    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound3.setBuffer(buffer3);
    sound1.setLoop(true);
    sound2.setLoop(true);
    sound3.setLoop(false);
    sound1.setAttenuation(.1);
    sound2.setAttenuation(.1);
    sound3.setAttenuation(.1);
    sound1.setMinDistance(10);
    sound2.setMinDistance(10);
    sound3.setMinDistance(10);
//    sound1.setRelativeToListener(true);
//    sound2.setRelativeToListener(true);
}

AudioComponent::~AudioComponent()
{
    sound1.stop();
    sound2.stop();
    sound3.stop();
    //dtor
}

ComponentBase::listenerList AudioComponent::getListeners()
{
    using namespace std::placeholders;
    auto handler = std::bind(&AudioComponent::HandleMovementChange, this, _1, _2, _3);
    listenerList out = listenerList();
    out.push_back(listenerPair(Events::HEALTH_CHANGE, handler));
    out.push_back(listenerPair(Events::DEATH, handler));
    return out;
}

//Looped function for audio instances
void AudioComponent::go(sf::Time, Entity* entity){
    std::shared_ptr<MovementComponent> action = entity->getMovement();
    std::shared_ptr<WorldPositionComponent> position = entity->getPosition();
    if(position!=nullptr)
    {
        sound1.setPosition(position->getPosition().x, 0, position->getPosition().y);
        sound2.setPosition(position->getPosition().x, 0, position->getPosition().y);
        sound3.setPosition(position->getPosition().y, 0, position->getPosition().y);
    }
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
        /*else if (action->getState()==0){
            sound3.setVolume(30);
            sound3.play();
            sound1.stop();
            sound2.stop();
        }*/
        else{
            //if no actions require sound, play no sound
            sound1.stop();
            sound2.stop();
        }
    }
}

void AudioComponent::HandleMovementChange(Events event, EventObj* obj, Entity* entity)
{
    switch(event)
    {
    case Events::HEALTH_CHANGE:
        //play some hurt message here
        break;
    case Events::DEATH:
        sound3.play();
        break;
    }
}
