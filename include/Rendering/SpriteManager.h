#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "Rendering/AnimatedSprite.h"
#include <string>
#include <unordered_map>
#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rendering/TextureManager.h"
#include <stdexcept>

//! Manages all sprites, animations, and animation sprites loaded from files, as well as methods to load the sprites
/*! \see sf::Sprite AnimatedSprite Animation */
class SpriteManager {
public:
	/** Default constructor */
	SpriteManager();
	/** Default destructor */
	~SpriteManager();

	//! Loads a file formated in our self-made XML type
	/*! This associates animations with an animated sprite, as well as a simple way to load animations
        \param input the file to load
        \return A bool value if successfully loaded or not */
	int loadFile(std::string input);
	//! Loads a sprite file
	/*! of "DarkFunction Editor" .sprite type
        \param input The filename of the .sprite file */
	void loadSpriteFile(std::string);

	//! Returns a sprite
	/*! \param input The name of the sprite */
	AnimatedSprite getSprite(std::string input);
	//! Adds a sprite to the manager
	/*! \param Name the name to store the Sprite by
        \param sprite The sprite to store
    */
	void addSprite(std::string name, AnimatedSprite sprite);
protected:
    void loadSpriteDirectory(std::string, rapidxml::xml_node<>*);
private:
	static std::unordered_map<std::string, AnimatedSprite> spriteMap;
	static TextureManager texMan;
};

#endif // SPRITEMANAGER_H
