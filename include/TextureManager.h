#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>

class TextureManager
{
    public:
        TextureManager();
        ~TextureManager();
        sf::Texture* addTexture(std::string file); //force-adds a texture, for preloading reasons
        static void flush(); //clears all cached textures
        sf::Texture* getTexture(std::string name); //Will automatically load a texture if needed, just input the filename

    protected:
    private:
        static std::unordered_map<std::string, sf::Texture*> textureMap;
};

#endif // TEXTUREMANAGER_H
