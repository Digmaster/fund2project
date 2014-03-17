#include "Rendering/TextureManager.h"

using namespace std;
using namespace sf;

TextureManager::TextureManager()
{
    //Creates the error Image
    //TODO: Make this say ERROR or something
    if(textureMap.find("error") == textureMap.end()) {
        sf::Image errorImg;
        errorImg.create(32,32, Color::Red);
        Texture* errorTex = new Texture();
        errorTex->loadFromImage(errorImg);
        textureMap.emplace("error", errorTex);
    }
}

std::unordered_map<std::string, sf::Texture*> TextureManager::textureMap;

TextureManager::~TextureManager()
{

}

sf::Texture* TextureManager::addTexture(string input) {
    if(textureMap.find(input) == textureMap.end()) {
        Texture* texture = new Texture();
        if (texture->loadFromFile(input.c_str()))
        {
            textureMap.emplace(input, texture);
            return texture;
        }
        else {
            cout << "ERROR: Texture " << input << " was not found! (Does it exist?)" << endl;
            return textureMap.at("error");
        }
    }
    else
        cout << "WARNING: Texture " << input << " already loaded!" << endl;;
        return textureMap.at(input);
}

void TextureManager::flush() {
    textureMap.clear();
}

Texture* TextureManager::getTexture(string input) {
    if(textureMap.find(input) == textureMap.end())
        return addTexture(input);
    else
        return textureMap.at(input);
}
