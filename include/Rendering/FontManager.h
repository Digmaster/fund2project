#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>

class FontManager
{
    public:
        FontManager();
        virtual ~FontManager();

        //! Adds a texture based on the filename
        /*! Force-adds a texture, for pre-loading . If the texture already exists it will be reloaded
            \param file The filename of the texture to be loaded
            \return A pointer to the loaded sf::Texture */
        static sf::Font* addFont(std::string file);
        //! Removes all loaded textures
        static void flush();
        //! Returns a texture by that filename
        /*! If the texture has not already been loaded, it will be loaded. Otherwise the copy in memory will be used
            \param name The filename of the texture
            \return A pointer to the sf::Texture */
        static sf::Font* getFont(std::string name); //Will automatically load a texture if needed, just input the filename

    protected:
    private:
        static std::unordered_map<std::string, sf::Font*> fontMap;
};

#endif // FONTMANAGER_H
