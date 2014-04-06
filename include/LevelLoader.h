#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class RenderEngine;
class TextureManager;

//! Contains all information pertaining to the currently loaded level, as well as the method for loading the level
/*! This class is mostly designed to load the level, as all information created from loading the level should be stored in the ComponentsManager,
    however specific information about the level is presented here (Such as it's width and height) */
class Level {
public:
    //! Default Constructor
    Level();
    //! Loads a level
    /*! Takes an XML file created by the Tiled level creator and loads it into memory
        \param filename The filename, relative to the binary's file
        \param RenderEngine* The RenderEngine contained in the Game Engine */
    void loadLevel(std::string filename, RenderEngine*);

    //! Standardized method to create a box
    void makeBox(sf::Sprite, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    void makeSensor(sf::Vector2f, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    void makeCamera(sf::Sprite, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    void makeBraveAdventurer(sf::Sprite, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    //! The width of the level, in "Tiles"
    int width;
    //! The height of the level, in "Tiles"
    int height;
private:
    sf::Color HexToColor(std::string);

    std::string version;
    std::string orientation;

    int tilewidth;
    int tileheight;

    TextureManager* texMan;

    std::map<int, sf::Sprite> sprites;
    std::map<std::string, std::string> mapProperties;
};

//DUN DUN DUN DUUUUUNNNNNNNNNNNN

#endif // LEVEL_H
