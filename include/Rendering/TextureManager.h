#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>

// HACK (Thomas Luppi#1#04/06/14): Place into Game ENgine, so it doesn't have to be singleton-esk


//! Stores and loads all textures contained in the game
/*! Acts as a texture cache
    All instances will share the same texture list. Explicitly call flush to clear all textures from memory, they will not be destroyed when the destructor is called
    \see sf::Texture */
class TextureManager
{
    public:
        //! Default constructor
        TextureManager();
        //! Default
        ~TextureManager();
        //! Adds a texture based on the filename
        /*! Force-adds a texture, for pre-loading . If the texture already exists it will be reloaded
            \param file The filename of the texture to be loaded
            \return A pointer to the loaded sf::Texture */
        sf::Texture* addTexture(std::string file); /
        //! Removes all loaded textures
        static void flush();
        //! Returns a texture by that filename
        /*! If the texture has not already been loaded, it will be loaded. Otherwise the copy in memory will be used
            \param name The filename of the texture
            \return A pointer to the sf::Texture */
        sf::Texture* getTexture(std::string name); //Will automatically load a texture if needed, just input the filename

    protected:
    private:
        static std::unordered_map<std::string, sf::Texture*> textureMap;
};

#endif // TEXTUREMANAGER_H
