/**************************************************************************
* This is going to be a horrible, thus why it has it's own file
* BUT HONESTLY HOLY JESUS
* life. life is no fun.
**************************************************************************/

#include <string>
#include "Rendering/TextureManager.h"
#include <map>
#include <SFML/Graphics.hpp>

class Level {
public:
    void loadLevel(std::string filename);
private:
    std::string version;
    std::string orientation;
    int width;
    int height;
    int tilewidth;
    int tileheight;

    TextureManager texMan;

    std::map<int, sf::Sprite> sprites;
};

//DUN DUN DUN DUUUUUNNNNNNNNNNNN
