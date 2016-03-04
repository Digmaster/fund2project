#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SFML/Audio.hpp>
#include <unordered_map>

class AudioManager
{
    public:
        //! Adds a sound based on the filename
        /*! Force-adds a sound, for pre-loading . If the sound already exists it will be reloaded
            \param file The filename of the sound to be loaded
            \return A pointer to the loaded sf::SoundBuffer */
        sf::SoundBuffer& addSound(std::string file);

        //! Removes all loaded sounds
        void flush();

        //! Returns a sound by that filename
        /*! If the sound has not already been loaded, it will be loaded. Otherwise the copy in memory will be used
            \param name The filename of the sound
            \return A pointer to the sf::SoundBuffer */
        sf::SoundBuffer& getSound(std::string name);

        //! Returns a pointer to the AudioManager singleton
        /*! \return pointer to the AudioManager singleton */
        static AudioManager& instance() {
            static AudioManager INSTANCE;
            return INSTANCE;
        }
    protected:
        AudioManager();
        static std::unordered_map<std::string, sf::SoundBuffer*> audioMap;
    private:
};

#endif // AUDIOMANAGER_H
