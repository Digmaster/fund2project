#include "FontManager.h"

using namespace std;
using namespace sf;

FontManager::FontManager()
{
    //ctor
}

FontManager::~FontManager()
{
    //dtor
}

std::unordered_map<std::string, sf::Font*> FontManager::fontMap;

sf::Font* FontManager::addFont(string input) {
    if(fontMap.find(input) == fontMap.end()) {
        Font* font = new Font();
        if (font->loadFromFile(input.c_str()))
        {
            fontMap.emplace(input, font);
            return font;
        }
        else {
            cout << "ERROR: Font " << input << " was not found! (Does it exist?)" << endl;
            return fontMap.at("error");
        }
    }
    else
        cout << "WARNING: Font " << input << " already loaded!" << endl;;
        return fontMap.at(input);
}

void FontManager::flush() {
    fontMap.clear();
}

Font* FontManager::getFont(string input) {
    if(fontMap.find(input) == fontMap.end())
        return addFont(input);
    else
        return fontMap.at(input);
}
