#include "SingleUseAudioComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/ComponentManager.h"

SingleUseAudioComponent::SingleUseAudioComponent(std::string soundFile, bool DestroyOnFinish)
{
    buffer.loadFromFile(soundFile);
    sound.setBuffer(buffer);
    sound.setLoop(!DestroyOnFinish);
    sound.setAttenuation(.1);
    sound.setMinDistance(10);
    sound.play();
}

SingleUseAudioComponent::~SingleUseAudioComponent()
{
    sound.stop();
}

void SingleUseAudioComponent::go(sf::Time, Entity* entity)
{
    std::shared_ptr<WorldPositionComponent> position = entity->getPosition();
    if(position!=nullptr)
    {
        sound.setPosition(position->getPosition().x, 0, position->getPosition().y);
    }
//    if(sound.getStatus()==sf::Sound::Stopped)
//        compMan->removeEntity(entity->getID());
}
