#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
    //ctor
}

std::unordered_map<std::string, sf::SoundBuffer*> AudioManager::audioMap;

sf::SoundBuffer& AudioManager::addSound(std::string input) {
    if(audioMap.find(input) == audioMap.end()) {
        sf::SoundBuffer* sound = new sf::SoundBuffer();
        if (sound->loadFromFile(input.c_str()))
        {
            audioMap.emplace(input, sound);
            return *sound;
        }
        else {
            std::cout << "ERROR: Sound " << input << " was not found! (Does it exist?)" << std::endl;
            return *audioMap.at("error");
        }
    }
    else
        std::cout << "WARNING: Sound " << input << " already loaded!" << std::endl;;
        return *audioMap.at(input);
}

void AudioManager::flush() {
    audioMap.clear();
}

sf::SoundBuffer& AudioManager::getSound(std::string input) {
    if(audioMap.find(input) == audioMap.end())
        return addSound(input);
    else
        return *audioMap.at(input);
}
