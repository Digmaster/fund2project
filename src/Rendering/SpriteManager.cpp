#include "Rendering/SpriteManager.h"

using namespace std;
using namespace sf;
using namespace rapidxml;

SpriteManager::SpriteManager() {

}

std::unordered_map<std::string, AnimatedSprite> SpriteManager::spriteMap;
TextureManager SpriteManager::texMan;

SpriteManager::~SpriteManager() {
	//dtor
}
// TODO (Thomas Luppi#1#03/19/14): Rewrite to use darkFunction editor output, so we don't have to manually make sprites.
int SpriteManager::loadFile(string input) { // NOTE (Thomas Luppi#3#03/16/14): Change to lazyloading somehow: Some sort of map, filled by going through all the files and looking for stuff perhaps?
	//Parse XML shiiiiiiiiiit
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream file (input);
	if(!file.good()) {
		cout << "Can not open file " << input << " to read file" << endl;
		return 1;
	}
	else {
		vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc
		try {
            doc.parse<0>(&buffer[0]);
		}
		catch(std::exception& e) {
            cout << "Error in parsing XML file " << input << ": " << e.what() << endl;
            return 1;
		}
		//find root node
		root_node = doc.first_node("SpriteSheet");

		//Top level with the imagefile
		string textureFile = root_node->first_attribute("file")->value();
		Texture *texture = texMan.getTexture(textureFile);

		//Iterate through sprites
		int numSprites=0;
		for (xml_node<> * sprite_node = root_node->first_node("Sprite"); sprite_node; sprite_node = sprite_node->next_sibling()) {
			string spriteName = sprite_node->first_attribute("name")->value();

			AnimatedSprite animatedSprite(true, false);
			//Iterate through all animations in sprite
			for(xml_node<> * animation_node = sprite_node->first_node("Animation"); animation_node; animation_node = animation_node->next_sibling()) {
				string animationName = animation_node->first_attribute("name")->value();
				xml_attribute<>* timePtr = animation_node->first_attribute("FT");
				float time = 0.2f;
				if(timePtr!=NULL)
                    time = atof(timePtr->value());
				Animation animation(sf::seconds(time));
				animation.setSpriteSheet(*texture);

				//Add all frames
				for(xml_node<> * frame_node = animation_node->first_node("Frame"); frame_node; frame_node = frame_node->next_sibling()) {
                        int LC = atoi(frame_node->first_attribute("LC")->value());
                        int TC = atoi(frame_node->first_attribute("TC")->value());
                        int W = atoi(frame_node->first_attribute("W")->value());
                        int H = atoi(frame_node->first_attribute("H")->value());
                        animation.addFrame(sf::IntRect(LC, TC, W, H)); //Add frame to animation
				}
				animatedSprite.addAnimation(animationName, animation); //Add animation to sprite
			}
			//Add default if it exists (Useful for single image sprites)
			xml_node<> * default_node = sprite_node->first_node("Default");
			if(default_node!=NULL) {
			    Animation animation(sf::seconds(.02f));
				animation.setSpriteSheet(*texture);
                int LC = atoi(default_node->first_attribute("LC")->value());
                int TC = atoi(default_node->first_attribute("TC")->value());
                int W = atoi(default_node->first_attribute("W")->value());
                int H = atoi(default_node->first_attribute("H")->value());
                animation.addFrame(sf::IntRect(LC, TC, W, H)); //Add frame to animation
                animatedSprite.addAnimation("default", animation); //Add animation to sprite
			}
			addSprite(spriteName, animatedSprite); //add sprite to spritemap
			numSprites++;
		}
		cout << numSprites << " sprites loaded from " << input << '.' << endl;
	}
	return 0;

}

void SpriteManager::addSprite(std::string name, AnimatedSprite sprite) {
    spriteMap.emplace(name, sprite); //add sprite to spritemap
}

AnimatedSprite SpriteManager::getSprite(std::string input) {
    try {
        return spriteMap.at(input);
    }
    catch (const std::out_of_range oor) {
        cout << "Unable to load sprite " << input << ". You done messed up somewhere" << endl;
        cout << oor.what() << endl;
    }
}
