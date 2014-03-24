#include "LevelLoader.h"
#include <rapidxml.hpp>
#include <iostream>

#include "Components/ComponentManager.h"
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/StaticSpriteComponent.h"

using namespace std;
using namespace sf;
using namespace rapidxml;

void Level::loadLevel(std::string filename) {
    /******************************
    * Parse XML file
    ******************************/
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	ifstream file (filename);
	if(!file.good()) {
		cout << "Can not open file " << filename << " to read file" << endl;
		return;
	}
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer using the xml file parsing library into doc
    try {
        doc.parse<0>(&buffer[0]);
    }
    catch(std::exception& e) {
        cout << "Error in parsing XML level file " << filename << ": " << e.what() << endl;
        return;
    }
    /******************************
    * Interpret!
    ******************************/
    ///Root map node
    root_node = doc.first_node("map");
    if(root_node!=NULL) {
        auto attribute = root_node->first_attribute("version");
        if(attribute!=NULL)
            version = attribute->value();

        attribute = root_node->first_attribute("orientation");
        if(attribute!=NULL)
            orientation = attribute->value();
        if(orientation!="orthogonal")
            throw runtime_error("Not orthogonal level!!! (Not implemented yet"); //It's essential that it's in the format that we can actually use

        attribute = root_node->first_attribute("width");
        if(attribute!=NULL)
            width = atoi(attribute->value());

        attribute = root_node->first_attribute("height");
        if(attribute!=NULL)
            height = atoi(attribute->value());

        attribute = root_node->first_attribute("tilewidth");
        if(attribute!=NULL)
            tilewidth = atoi(attribute->value());

        attribute = root_node->first_attribute("tileheight");
        if(attribute!=NULL)
            tileheight = atoi(attribute->value());

    }
    else
        throw runtime_error("Could not find root map node");
    ///Tilesets!
    for (xml_node<>* tileset_node = root_node->first_node("tileset"); tileset_node; tileset_node = tileset_node->next_sibling()) {
        auto attribute = root_node->first_attribute("firstgid");
        int firstgid = 1;
        if(attribute!=NULL)
            firstgid = atoi(attribute->value());
        else
            throw runtime_error("No firstgid found for tileset");

        attribute = root_node->first_attribute("source");
        if(attribute!=NULL) {
            ///Load from .tsx file!!!!!!!!!
        }
        else {
            ///Simple tileset, loaded on the fly
            //Data needed for the tileset
            int ttilewidth = tilewidth;
            int ttileheight = tileheight;
            attribute = tileset_node->first_attribute("name");
            if(attribute!=NULL){
                //Not sure if we need name, but just in case
                //tileheight = attribute->value();
            }
            attribute = tileset_node->first_attribute("tilewidth");
            if(attribute!=NULL)
                ttilewidth = atoi(attribute->value());

            attribute = tileset_node->first_attribute("tileheight");
            if(attribute!=NULL)
                ttileheight = atoi(attribute->value());

            ///Images in simple tileset
            for (xml_node<>* image_node = tileset_node->first_node("image"); image_node; image_node = image_node->next_sibling()) {

                sf::Texture* texture;
                attribute = image_node->first_attribute("source");
                if(attribute!=NULL)
                    texture = texMan.getTexture(attribute->value());

                sf::Color trans;
                attribute = image_node->first_attribute("trans");
                if(attribute!=NULL)
                    cout << "Color masks not yet implemented" << endl;

                int textureWidth = texture->getSize().x;
                attribute = image_node->first_attribute("width");
                if(attribute!=NULL)
                    textureWidth = atoi(attribute->value());

                int textureHeight = texture->getSize().y;
                attribute = image_node->first_attribute("height");
                if(attribute!=NULL)
                    textureWidth = atoi(attribute->value());

                ///Load all sprites!
                int numWidth = textureWidth/ttilewidth;
                int numHeight = textureHeight/ttileheight;
                for(int i = firstgid, j = 0; i < numWidth*numHeight; i++, j++) {
                    IntRect textureRect = IntRect((j%numWidth)*ttilewidth, (j/numWidth)*ttileheight, ttilewidth, ttileheight);
                    sprites[i].setTexture(*texture);
                    sprites[i].setTextureRect(textureRect);
                } //tile loop
            } //image
        } //simple tileset if
    } //tilesets

    ///Layers!!!!
    for (xml_node<>* layer_node = root_node->first_node("layer"); layer_node; layer_node = layer_node->next_sibling()) {
        auto attribute = layer_node->first_attribute("name");
        if(attribute!=NULL) {
            //Just as before, not sure if we need the name
        }

        int layerWidth;
        attribute = layer_node->first_attribute("width");
        if(attribute!=NULL)
            layerWidth = atoi(attribute->value());

        int layerHeight;
        attribute = layer_node->first_attribute("height");
        if(attribute!=NULL)
            layerHeight = atoi(attribute->value());

        ///Layer Properties
        map<string, string> properties;
        for (xml_node<>* properties_node = layer_node->first_node("properties"); properties_node; properties_node = properties_node->next_sibling()) {
            for (xml_node<>* property_node = properties_node->first_node("property"); property_node; property_node = property_node->next_sibling()) {
                string propertyName;
                attribute = property_node->first_attribute("name");
                if(attribute!=NULL)
                    propertyName = attribute->value();
                string propertyValue;
                attribute = property_node->first_attribute("value");
                if(attribute!=NULL)
                    propertyValue = attribute->value();
            }
        }

        ///Data!! // TODO (Thomas Luppi#1#03/24/14): Allow compression
        for (xml_node<>* data_node = layer_node->first_node("data"); data_node; data_node = data_node->next_sibling()) {
            int i = 0;
            for (xml_node<>* tile_node = data_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling()) {
                int tileGid;
                attribute = layer_node->first_attribute("gid");
                if(attribute!=NULL)
                    tileGid = atoi(attribute->value());
                if(tileGid!=0) {
                    Vector2f position = Vector2f((i%layerWidth)*tilewidth, (i/layerHeight)*tileheight);
                    int id = ComponentManager::getInst().getNewID();
                    WorldPositionComponent* posComp = new WorldPositionComponent(id);
                    posComp->setPosition(position);
                    StaticSpriteComponent* sprite = new StaticSpriteComponent(sprites[tileGid],id);
                    if (properties.find("solid") != properties.end()) {
                        if(properties["solid"]!="no")
                          SimpleBoxPhysics* phys = new SimpleBoxPhysics(id,tilewidth,tileheight);
                    } //issolid
                } //is actually a tile
                i++;
            } //every tile
        } //every data node in layer (Should always be one)
    } //every layer
}






