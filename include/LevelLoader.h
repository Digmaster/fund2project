#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <rapidxml.hpp>

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
        \param filename The filename of the tmx file to load
        \param RenderEngine* The RenderEngine contained in the Game Engine */
    void loadLevel(std::string filename, RenderEngine*);

    //! The width of the level, in "Tiles"
    int width;
    //! The height of the level, in "Tiles"
    int height;
private:
    void createSimpleSolidBounds(int layerWidth, int layerHeight, int tilewidth, int layerNum, float transparency, std::map<std::string, std::string>, bool visible, rapidxml::xml_node<>* data_node);
    void createFilledSolidBounds(int layerWidth, int layerHeight, int tilewidth, int layerNum, float transparency, std::map<std::string, std::string>, bool visible, rapidxml::xml_node<>* data_node);

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
