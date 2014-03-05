#include "SpriteManager.h"

using namespace std;
using namespace sf;
using namespace rapidxml;

SpriteManager::SpriteManager() {

}

SpriteManager::~SpriteManager() {
	//dtor
}

void SpriteManager::loadFile(string input) {
	//Create the sprite
	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	//Parse XML shiiiiiiiiiit
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream file (input);
	if(!file.good())
		throw runtime_error("Unable to open XML file");
	else {
		vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc
		try {
            doc.parse<0>(&buffer[0]);
		}
		catch(std::exception& e) {
            cout << "Error in parsing XML file " << input << ": "
            << e.what() << endl;
		}
		//find root node
		root_node = doc.first_node("SpriteSheet");

		//Top level with the imagefile
		// TODO (Thomas Luppi#1#): Enable multiple spritesheets per file? Should we do this?
		string textureFile = root_node->first_attribute("file")->value();
		Texture *texture = TextureManager::inst().getTexture(textureFile);

		//Iterate through sprites
		int numSprites=0;
		for (xml_node<> * sprite_node = root_node->first_node("Sprite"); sprite_node; sprite_node = sprite_node->next_sibling()) {
			string spriteName = sprite_node->first_attribute("name")->value();

			//Iterate through all animations in sprite
			for(xml_node<> * animation_node = sprite_node->first_node("Animation"); animation_node; animation_node = animation_node->next_sibling()) {
				string animationName = animation_node->first_attribute("name")->value();
				Animation animation;

				//Add all frames
				for(xml_node<> * frame_node = animation_node->first_node("Frame"); frame_node; frame_node = frame_node->next_sibling()) {
					animation.setSpriteSheet(*texture);
					int LC = atoi(frame_node->first_attribute("LC")->value());
					int TC = atoi(frame_node->first_attribute("TC")->value());
					int W = atoi(frame_node->first_attribute("W")->value());
					int H = atoi(frame_node->first_attribute("H")->value());
					animation.addFrame(sf::IntRect(LC, TC, W, H)); //Add fram to animation
				}
				animatedSprite.addAnimation(animationName, animation); //Add animation to sprite
			}
			spriteMap.emplace(spriteName, animatedSprite); //add sprite to spritemap
			numSprites++;
		}
		cout << numSprites << " sprites loaded from " << input << '.' << endl;
	}

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
