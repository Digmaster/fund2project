#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "AnimatedSprite.h"
#include <string>
#include <unordered_map>
#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <stdexcept>

class SpriteManager {
public:
	/** Default constructor */
	SpriteManager();
	/** Default destructor */
	~SpriteManager();
	void loadFile(std::string input);
	AnimatedSprite getSprite(std::string input);
	void addSprite(std::string name, AnimatedSprite sprite);

	static SpriteManager& inst() { //SWEET BABY JESUS ITS ANOTHER SINGLETON
	    // TODO (Thomas Luppi#2#03/04/14): Somehow make this not a Singleton
        static SpriteManager INSTANCE;
        return INSTANCE;
	}
protected:
private:
	std::unordered_map<std::string, AnimatedSprite> spriteMap;
};

#endif // SPRITEMANAGER_H
