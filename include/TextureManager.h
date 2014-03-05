#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureManager
{
    public:
        TextureManager();
        ~TextureManager();
        sf::Texture* addTexture(std::string file); //force-adds a texture, for preloading reasons
        void flush(); //clears all cached textures
        sf::Texture* getTexture(std::string name); //Will automatically load a texture if needed, just input the filename

        static TextureManager& inst() { //DIRTY ROTTEN SINGLETON. Please don't abuse this simple implementation
            static TextureManager INSTANCE;
            return INSTANCE;
        }

    protected:
    private:
        std::unordered_map<std::string, sf::Texture*> textureMap;
};

#endif // TEXTUREMANAGER_H
