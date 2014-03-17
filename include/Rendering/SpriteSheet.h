#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <map>
#include "AnimationHolder.h"
#include "rapidxml.hpp"
#include "TextureManager.h"

class SpriteSheet
{
    public:
        /** Default constructor */
        SpriteSheet();
        /** Default destructor */
        virtual ~SpriteSheet();
        void load(std::string input);
        void save();
        void setFileName(std::string name) {fileName = name;}
        void setImageFile(std::string name);
        static void setRendEngine(RenderEngine* input) {
            SpriteSheet::rendEng = input;
        }
    protected:
    private:
        std::string fileName;
        std::string textureFile;
        sf::Texture texture;
        sf::Sprite theSheet;
        std::map<std::string, AnimationHolder> sprites;

};

#endif // SPRITESHEET_H
