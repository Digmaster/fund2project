#ifndef LEVEL_H
#define LEVEL_H

/**************************************************************************
* This is going to be a horrible, thus why it has it's own file
* BUT HONESTLY HOLY JESUS
* life. life is no fun.
**************************************************************************/

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class RenderEngine;
class TextureManager;

class Level {
public:
    Level();
    void loadLevel(std::string filename, RenderEngine*);

    void makeBox(sf::Sprite, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    void makeSensor(sf::Vector2f, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    void makeCamera(sf::Sprite, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);
    void makeBraveAdventurer(sf::Sprite, sf::Vector2f, std::map<std::string, std::string>, int layer, std::string);

    int width;
    int height;
private:
    sf::Color HexToColor(std::string);

    std::string version;
    std::string orientation;

    int tilewidth;
    int tileheight;

    TextureManager* texMan;

    std::map<int, sf::Sprite> sprites;
};

//DUN DUN DUN DUUUUUNNNNNNNNNNNN

#endif // LEVEL_H
