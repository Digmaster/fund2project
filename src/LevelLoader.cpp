#include "LevelLoader.h"
#include <rapidxml.hpp>
#include <iostream>


#include <stdexcept>
#include "Components/Physics/SimpleBoxPhysics.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Render/StaticSpriteComponent.h"
#include "Rendering/RenderEngine.h"
#include "Components/Identification/IDComponent.h"
#include "Components/Script/Camera.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Render/BraveAdventurerAnimatedComponent.h"
#include "Components/Movement/BraveAdventurerMovement.h"
#include "Rendering/SpriteManager.h"
#include "Components/Input/BraveAdventurerInput.h"
#include "Components/Physics/BoundaryPhysics.h"



using namespace std;
using namespace sf;
using namespace rapidxml;

Level::Level() {
    texMan = new TextureManager;

}

void Level::loadLevel(std::string filename, RenderEngine* rendEng) {
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

        attribute = root_node->first_attribute("backgroundcolor");
        if(attribute!=NULL)
            rendEng->setBackgroundColor(HexToColor(attribute->value()));

        for (xml_node<>* properties_node = root_node->first_node("properties"); properties_node; properties_node = properties_node->next_sibling()) {
            for (xml_node<>* property_node = properties_node->first_node("property"); property_node; property_node = property_node->next_sibling()) {
                string propertyName;
                attribute = property_node->first_attribute("name");
                if(attribute!=NULL)
                    propertyName = attribute->value();
                string propertyValue;
                attribute = property_node->first_attribute("value");
                if(attribute!=NULL)
                    propertyValue = attribute->value();
                mapProperties[propertyName]=propertyValue;
            }
        }
    }
    else
        throw runtime_error("Could not find root map node");
    bool doBoundaries = true;
    if (mapProperties.find("boundaries") != mapProperties.end()) {
        if(mapProperties["boundaries"]=="no") {
            doBoundaries=false;
        }
    }
    if(doBoundaries) {
        ///Collision Boundaries
        //Left
        int id = ComponentBase::getNewID();
        BoundaryPhysics leftBoundary(id, 0, -1000, 0, height*tileheight-tileheight/2);
        //right
        id = ComponentBase::getNewID();
        BoundaryPhysics rightBoundary(id, width*tilewidth-tilewidth/2, -1000, width*tilewidth-tilewidth/2, height*tileheight-tileheight/2);
        //bottom
        /*id = ComponentBase::getNewID();
        BoundaryPhysics bottomBoundary(id, 0, height*tileheight-tileheight/2, width*tilewidth-tilewidth/2, height*tileheight-tileheight/2);*/
        //top
        id = ComponentBase::getNewID();
        BoundaryPhysics topBoundary(id, 0, -1000, width*tilewidth-tilewidth/2, -1000);
    }


    ///Tilesets!
    for (xml_node<>* tileset_node = root_node->first_node("tileset"); tileset_node; tileset_node = tileset_node->next_sibling()) {
        auto attribute = tileset_node->first_attribute("firstgid");
        int firstgid = 0;
        if(attribute!=NULL)
            firstgid = atoi(attribute->value());

        if(firstgid!=0) { //For some reason it loads all images....POS.
            attribute = tileset_node->first_attribute("source");
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
                    if(attribute!=NULL) {
                        texture = texMan->getTexture(attribute->value());
                    }


                    sf::Color trans;
                    attribute = image_node->first_attribute("trans");
                    if(attribute!=NULL) {
                        //trans = HexToColor(attribute->value());
                        //SFML can't easily do this, so it's here in case you want to do something with it, but it won't do anything right now
                    }

                    int textureWidth = texture->getSize().x;
                    attribute = image_node->first_attribute("width");
                    if(attribute!=NULL)
                        textureWidth = atoi(attribute->value());

                    int textureHeight = texture->getSize().y;
                    attribute = image_node->first_attribute("height");
                    if(attribute!=NULL)
                        textureHeight = atoi(attribute->value());

                    ///Load all sprites!
                    int numWidth = textureWidth/ttilewidth;
                    int numHeight = textureHeight/ttileheight;
                    for(int i = firstgid, j = 0; j < numWidth*numHeight; i++, j++) {
                        IntRect textureRect = IntRect((j%numWidth)*ttilewidth, (j/numWidth)*ttileheight, ttilewidth, ttileheight);
                        sprites[i].setTexture(*texture);
                        sprites[i].setTextureRect(textureRect);
                    } //tile loop
                } //image
            } //simple tileset if
        }
    } //tilesets

    ///Layers!!!!
    int layerNum = 1;
    for (xml_node<>* layer_node = root_node->first_node(); layer_node; layer_node = layer_node->next_sibling()) {
        string nodename = layer_node->name();

        ///Layer Properties
        map<string, string> properties;
        for (xml_node<>* properties_node = layer_node->first_node("properties"); properties_node; properties_node = properties_node->next_sibling()) {
            for (xml_node<>* property_node = properties_node->first_node("property"); property_node; property_node = property_node->next_sibling()) {
                string propertyName;
                auto attribute = property_node->first_attribute("name");
                if(attribute!=NULL)
                    propertyName = attribute->value();
                string propertyValue;
                attribute = property_node->first_attribute("value");
                if(attribute!=NULL)
                    propertyValue = attribute->value();
                properties[propertyName]=propertyValue;
            }
        }

        if(nodename=="layer") {
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


            ///Data!!
            // TODO (Thomas Luppi#1#03/24/14): Allow compression
            for (xml_node<>* data_node = layer_node->first_node("data"); data_node; data_node = data_node->next_sibling()) {
                int i = 0;
                vector< vector<bool> >collissionMap(layerWidth+1, vector<bool>(layerHeight+1, false));
                for (xml_node<>* tile_node = data_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling()) {
                    int tileGid = 0;
                    attribute = tile_node->first_attribute("gid");
                    if(attribute!=NULL)
                        tileGid = atoi(attribute->value());
                    if(tileGid!=0) {
                        Vector2f position = Vector2f((int)(i%layerWidth)*tilewidth, (int)(i/layerWidth)*tileheight);
                        int id = ComponentBase::getNewID();
                        WorldPositionComponent* posComp = new WorldPositionComponent(id);
                        posComp->setPosition(position);
                        posComp->setLayer(layerNum);
                        StaticSpriteComponent* sprite = new StaticSpriteComponent(sprites[tileGid], id);
                        if (properties.find("solid") != properties.end()) {
                            if(properties["solid"]!="no")
                              //SimpleBoxPhysics* phys = new SimpleBoxPhysics(id,tilewidth,tileheight, true, false, false);
                              collissionMap[(int)(i%layerWidth)][(int)(i/layerWidth)] = true;
                        } //issolid
                    } //is actually a tile
                    i++;
                } //every tile
                ///Creating collision boundaries based on Collission map
                //on X surfaces
                for(int i = 1; i <= layerHeight; i++) {
                    bool lastCollission = false;
                    int startPoint = 0;
                    for(int j = 1; j <= layerWidth; j++) {
                        if(lastCollission && collissionMap[j][i]==true && collissionMap[j][i-1]==false) {
                            lastCollission = true;
                        }
                        else if(!lastCollission && collissionMap[j][i]==true && collissionMap[j][i-1]==false) {
                            //Start the collission line
                            startPoint = j*tilewidth-tilewidth/2;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[j][i]==false || collissionMap[j][i-1]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            BoundaryPhysics floor(id, startPoint, i*tileheight-tileheight/2, j*tilewidth-tilewidth/2, i*tileheight-tileheight/2);
                            lastCollission = false;
                        }
                    }
                }
                for(int i = 0; i <= layerHeight; i++) {
                    bool lastCollission = false;
                    int startPoint = 0;
                    for(int j = 0; j <= layerWidth; j++) {
                        if(lastCollission && collissionMap[j][i]==true && collissionMap[j][i+1]==false) {
                            lastCollission = true;
                        }
                        else if(!lastCollission && collissionMap[j][i]==true && collissionMap[j][i+1]==false) {
                            //Start the collission line
                            startPoint = j*tilewidth-tilewidth/2;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[j][i]==false || collissionMap[j][i+1]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            BoundaryPhysics floor(id, startPoint, i*tileheight+tileheight/2, j*tilewidth-tilewidth/2, i*tileheight+tileheight/2);
                            lastCollission = false;
                        }
                    }
                }
                for(int i = 1; i <= layerWidth; i++) {
                    bool lastCollission = false;
                    int startPoint = 0;
                    for(int j = 1; j <= layerHeight; j++) {
                        if(lastCollission && collissionMap[i][j]==true && collissionMap[i-1][j]==false) {
                            lastCollission = true;
                        }
                        else if(!lastCollission && collissionMap[i][j]==true && collissionMap[i-1][j]==false) {
                            //Start the collission line
                            startPoint = j*tilewidth-tilewidth/2;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[i][j]==false || collissionMap[i-1][j]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            BoundaryPhysics floor(id, i*tilewidth-tilewidth/2, startPoint, i*tilewidth-tilewidth/2, j*tileheight-tileheight/2);

                            lastCollission = false;
                        }
                    }
                }
                for(int i = 0; i <= layerWidth; i++) {
                    bool lastCollission = false;
                    int startPoint = 0;
                    for(int j = 0; j <= layerHeight; j++) {
                        if(lastCollission && collissionMap[i][j]==true && collissionMap[i+1][j]==false) {
                            lastCollission = true;
                        }
                        else if(!lastCollission && collissionMap[i][j]==true && collissionMap[i+1][j]==false) {
                            //Start the collission line
                            startPoint = j*tilewidth-tilewidth/2;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[i][j]==false || collissionMap[i+1][j]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            BoundaryPhysics floor(id, i*tilewidth+tilewidth/2, startPoint, i*tilewidth+tilewidth/2, j*tileheight-tileheight/2);

                            lastCollission = false;
                        }
                    }
                }
            } //every data node in layer (Should always be one)
        }
        else if(nodename=="imagelayer") {
            if( xml_node<>* image_node = layer_node->first_node("image")) {
                sf::Texture* texture;
                auto attribute = image_node->first_attribute("source");
                if(attribute!=NULL) {
                    texture = texMan->getTexture(attribute->value());
                    if(properties["tiled"]!="no") {
                        for(int i = texture->getSize().x/2-tilewidth/2; i < width*tilewidth+texture->getSize().x/2; i+=texture->getSize().x) {
                            for(int j = texture->getSize().y/2-tileheight/2; j < height*tileheight+texture->getSize().y/2; j+=texture->getSize().y) {
                                int id = ComponentBase::getNewID();
                                WorldPositionComponent* posComp = new WorldPositionComponent(id);
                                posComp->setPosition(Vector2f(i,j));
                                posComp->setLayer(layerNum);
                                Sprite imageSprite(*texture);
                                StaticSpriteComponent* sprite = new StaticSpriteComponent(imageSprite, id);
                            }
                        }
                    }
                    else {
                        int id = ComponentBase::getNewID();
                        WorldPositionComponent* posComp = new WorldPositionComponent(id);
                        posComp->setPosition(Vector2f(texture->getSize().x/2-tilewidth/2,texture->getSize().y/2-tileheight/2));
                        posComp->setLayer(layerNum);
                        Sprite imageSprite(*texture);
                        StaticSpriteComponent* sprite = new StaticSpriteComponent(imageSprite, id);
                    }
                }
            }
        }
        else if(nodename=="objectgroup") {
            for(xml_node<>* object_node = layer_node->first_node("object"); object_node; object_node=object_node->next_sibling()) {
                string type;
                auto attribute = object_node->first_attribute("type");
                if(attribute!=NULL)
                    type = attribute->value();

                string objectName = "none";
                attribute = object_node->first_attribute("name");
                if(attribute!=NULL)
                    objectName = attribute->value();

                int objGid=0;
                attribute = object_node->first_attribute("gid");
                if(attribute!=NULL)
                    objGid = atoi(attribute->value());

                int objectX;
                attribute = object_node->first_attribute("x");
                if(attribute!=NULL)
                    objectX = atoi(attribute->value());

                int objectY;
                attribute = object_node->first_attribute("y");
                if(attribute!=NULL)
                    objectY = atoi(attribute->value());

                int objectHeight;
                attribute = object_node->first_attribute("height");
                if(attribute!=NULL)
                    objectHeight = atoi(attribute->value());

                int objectWidth;
                attribute = object_node->first_attribute("width");
                if(attribute!=NULL)
                    objectWidth = atoi(attribute->value());

                map<string, string> objProperties;
                for (xml_node<>* properties_node = object_node->first_node("properties"); properties_node; properties_node = properties_node->next_sibling()) {
                    for (xml_node<>* property_node = properties_node->first_node("property"); property_node; property_node = property_node->next_sibling()) {
                        string propertyName;
                        attribute = property_node->first_attribute("name");
                        if(attribute!=NULL)
                            propertyName = attribute->value();
                        string propertyValue;
                        attribute = property_node->first_attribute("value");
                        if(attribute!=NULL)
                            propertyValue = attribute->value();
                        objProperties[propertyName]=propertyValue;
                    }
                }

                if(type=="box")
                    makeBox(sprites[objGid],Vector2f(objectX,objectY), objProperties, layerNum, objectName);
                if(type=="sensor")
                    makeSensor(Vector2f(objectWidth, objectHeight),Vector2f(objectX,objectY), objProperties, layerNum, objectName);
                if(type=="camera")
                    makeCamera(sprites[objGid],Vector2f(objectX,objectY), objProperties, layerNum, objectName);
                if(type=="BraveAdventurer")
                    makeBraveAdventurer(sprites[objGid],Vector2f(objectX,objectY), objProperties, layerNum, objectName);
            }
        }
        layerNum++;
    } //every layer
}



sf::Color Level::HexToColor(std::string input) {
    std::stringstream str;
    str << input.at(1);
    str << input.at(2);
    int red;
    str >> std::hex >> red;

    std::stringstream str2;
    str2 << input.at(3);
    str2 << input.at(4);
    int blue;
    str2 >> std::hex >> blue;

    std::stringstream str3;
    str3 << input.at(5);
    str3 << input.at(6);
    int green;
    str3 >> std::hex >> green;

    return sf::Color(red, blue, green);
}

void Level::makeBox(sf::Sprite sprite, sf::Vector2f position, std::map<string, string> properties, int layer, string name) {
    //position.x +=sprite.getGlobalBounds().width/2;
    position.y -=sprite.getGlobalBounds().height/2;
    unsigned int id = ComponentBase::getNewID();
    StaticSpriteComponent* spriteComp = new StaticSpriteComponent(sprite, id);

    WorldPositionComponent* posComp= new WorldPositionComponent(id);
    posComp->setPosition(position);
    posComp->setLayer(layer);

    SimpleBoxPhysics* physComp = new SimpleBoxPhysics(id, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height, false, true, false, false);

    if (name!="none")
        IDComponent* identification = new IDComponent(id, name);
}

void Level::makeSensor(sf::Vector2f dimension, sf::Vector2f position, std::map<string, string> properties, int layer, string name) {

    //Simple makeSensor without a sprite. Cannot figure out why the position is messed up.
    position.y +=dimension.y/2;
   /* if(dimension.x > dimension.y){
        position.x +=dimension.x/8;
        position.y -=dimension.y/8;
    }
    else{
        position.x -=dimension.x/8;
        position.y +=dimension.y/8;

    } */
    unsigned int id = ComponentBase::getNewID();
    //StaticSpriteComponent* spriteComp = new StaticSpriteComponent(sprite, id);

    WorldPositionComponent* posComp= new WorldPositionComponent(id);
    posComp->setPosition(position);
    posComp->setLayer(layer);

    SimpleBoxPhysics* physComp = new SimpleBoxPhysics(id, dimension.x, dimension.y, true, false, false, true);

    if (name!="none")
        IDComponent* identification = new IDComponent(id, name);
}

void Level::makeCamera(sf::Sprite sprite, sf::Vector2f position, std::map<std::string, std::string> properties, int layer, std::string name) {
    unsigned int id = ComponentBase::getNewID();
    Camera* camComp = new Camera(id, width, height);
    if (properties.find("target") != properties.end()) {
        TargetComponent* tarComp = new TargetComponent(id, properties["target"]);
    }
    if (name!="none")
        IDComponent* identification = new IDComponent(id, name);

}

void Level::makeBraveAdventurer(sf::Sprite sprite, sf::Vector2f position, std::map<std::string, std::string> properties, int layer, std::string name) {
    unsigned int id = ComponentBase::getNewID();
    BraveAdventurerAnimatedComponent* testSprite = new BraveAdventurerAnimatedComponent(id);
    SpriteManager spriteMan;
    //testSprite->setSprite(spriteMan.getSprite("BraveAdventurer"));
    testSprite->setSprite(spriteMan.getSprite("Samus"));
    testSprite->sprite.setAnimation("WalkUp");

    WorldPositionComponent* testPosition = new WorldPositionComponent(id);
    testPosition->setPosition(position);
    testPosition->setLayer(layer);

    BraveAdventurerInput* testInput = new BraveAdventurerInput(id);

    BraveAdventurerMovement* testMovement = new BraveAdventurerMovement(id);

    SimpleBoxPhysics* testPhys = new SimpleBoxPhysics(id,34,42,false, false, true, false);
    testPhys->setRotatable(false);

    if (properties.find("target") != properties.end()) {
        TargetComponent* tarComp = new TargetComponent(id, properties["target"]);
    }
    if (name!="none")
        IDComponent* identification = new IDComponent(id, name);
}
