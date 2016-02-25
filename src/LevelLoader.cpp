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
#include "Components/Physics/BoundaryPhysics.h"
#include "Components/Input/KeyboardInput.h"
#include "Components/Physics/PolygonPhysics.h"
#include "Components/Physics/PolylinePhysics.h"
#include "Components/Audio/AudioComponent.h"
#include "Components/Movement/EnemyMovement.h"
#include "Components/Stats/StatsComponent.h"
#include "Components/Script/MainCharScript.h"
#include "Components/Script/EnemySpawner.h"
#include "Components/Script/KillScript.h"
#include "Components/Entity.h"
#include "Components/Input/BasicAIInput.h"
#include "Components/Render/TextComponent.h"
#include "Components/Script/TeleportScript.h"
#include "Components/Script/ExplodeScript.h"
#include "Components/Physics/EllipsePhysics.h"
#include "Components/Movement/PathFollowMovement.h"

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
        Entity* entity = new Entity(id);
        entity->setPhysics(std::make_shared<BoundaryPhysics>(id, 0, -1000, 0, height*tileheight-tileheight/2));
        ComponentManager::getInst().addEntity(id, entity);
        //right
        id = ComponentBase::getNewID();
        entity = new Entity(id);
        entity->setPhysics(std::make_shared<BoundaryPhysics>(id, width*tilewidth-tilewidth/2, -1000, width*tilewidth-tilewidth/2, height*tileheight-tileheight/2));
        ComponentManager::getInst().addEntity(id, entity);
        //bottom
        id = ComponentBase::getNewID();
        entity = new Entity(id);
        entity->setPhysics(std::make_shared<BoundaryPhysics>(id, 0, height*tileheight-tileheight/2, width*tilewidth-tilewidth/2, height*tileheight-tileheight/2, PhysicsOptions::sensor));
        entity->addScript(std::make_shared<KillScript>(false, -1, sf::Time::Zero));
        ComponentManager::getInst().addEntity(id, entity);
        //top
        id = ComponentBase::getNewID();
        entity = new Entity(id);
        entity->setPhysics(std::make_shared<BoundaryPhysics>(id, 0, -1000, width*tilewidth-tilewidth/2, -1000));
        ComponentManager::getInst().addEntity(id, entity);

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
        float layerZoom = 1;
        if (properties.find("zoom") != properties.end())
            layerZoom = atof(properties["zoom"].c_str());
        rendEng->setLayerZoom(layerNum,layerZoom);
        bool noMove = false;
        if (properties.find("static") != properties.end())
            noMove = atoi(properties["static"].c_str());
        rendEng->setLayerMove(layerNum,noMove);

        float transparency=1;
        auto attribute = layer_node->first_attribute("opacity");
        if(attribute!=NULL) {
            transparency = atof(attribute->value());
        }

        bool visible=1;
        attribute = layer_node->first_attribute("visible");
        if(attribute!=NULL) {
            visible = atoi(attribute->value());
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
                        Vector2f position = Vector2f((int)(i%layerWidth)*tilewidth+tilewidth/2, (int)(i/layerWidth)*tileheight+tileheight/2);
                        int id = ComponentBase::getNewID();
                        Entity* entity = new Entity(id);
                        ComponentManager::getInst().addEntity(id, entity);
                        entity->setPosition(std::make_shared<WorldPositionComponent>(position, layerNum));
                        if(visible) {
                            sf::Sprite intermSpr(sprites[tileGid]);
                            intermSpr.setColor(sf::Color(255, 255, 255, transparency*255)); //Applies transparency mask
                            entity->setRender(std::make_shared<StaticSpriteComponent>(intermSpr));
                        }
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
                            startPoint = j*tilewidth;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[j][i]==false || collissionMap[j][i-1]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            Entity* entity = new Entity(id);
                            entity->setPhysics(std::make_shared<BoundaryPhysics>(id, startPoint, i*tileheight, j*tilewidth, i*tileheight));
                            ComponentManager::getInst().addEntity(id, entity);
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
                            startPoint = j*tilewidth;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[j][i]==false || collissionMap[j][i+1]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            Entity* entity = new Entity(id);

                            entity->setPhysics(std::make_shared<BoundaryPhysics>(id, startPoint, i*tileheight+tileheight, j*tilewidth, i*tileheight+tileheight));
                            ComponentManager::getInst().addEntity(id, entity);
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
                            startPoint = j*tilewidth;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[i][j]==false || collissionMap[i-1][j]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();

                            Entity* entity = new Entity(id);
                            entity->setPhysics(std::make_shared<BoundaryPhysics>(id, i*tilewidth, startPoint, i*tilewidth, j*tileheight));
                            ComponentManager::getInst().addEntity(id, entity);

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
                            startPoint = j*tilewidth;
                            lastCollission = true;
                        }
                        else if(lastCollission && (collissionMap[i][j]==false || collissionMap[i+1][j]==true)) {
                            //End it, and create it
                            int id = ComponentBase::getNewID();
                            Entity* entity = new Entity(id);
                            entity->setPhysics(std::make_shared<BoundaryPhysics>(id, i*tilewidth+tilewidth, startPoint, i*tilewidth+tilewidth, j*tileheight));
                            ComponentManager::getInst().addEntity(id, entity);

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
                        for(int i = (texture->getSize().x)/2-texture->getSize().x; i < width*tilewidth*layerZoom+texture->getSize().x/2; i+=texture->getSize().x) {
                            for(int j = (texture->getSize().y)/2-texture->getSize().y; j < height*tileheight*layerZoom+texture->getSize().y/2; j+=texture->getSize().y) {
                                int id = ComponentBase::getNewID();
                                Entity* entity = new Entity(id);
                                entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(i,j), layerNum));
                                Sprite imageSprite(*texture);
                                entity->setRender(std::make_shared<StaticSpriteComponent>(imageSprite));
                                ComponentManager::getInst().addEntity(id, entity);
                            }
                        }
                    }
                    else {
                        int id = ComponentBase::getNewID();
                        Entity* entity = new Entity(id);
                        entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(texture->getSize().x/2,texture->getSize().y/2), layerNum));
                        Sprite imageSprite(*texture);
                        entity->setRender(std::make_shared<StaticSpriteComponent>(imageSprite));
                        ComponentManager::getInst().addEntity(id, entity);
                    }
                }
            }
        }
        else if(nodename=="objectgroup") {
            for(xml_node<>* object_node = layer_node->first_node("object"); object_node; object_node=object_node->next_sibling()) {
                string type = "none";
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

                int objectX=0;
                attribute = object_node->first_attribute("x");
                if(attribute!=NULL)
                    objectX = atoi(attribute->value());

                int objectY=0;
                attribute = object_node->first_attribute("y");
                if(attribute!=NULL)
                    objectY = atoi(attribute->value());

                int objectHeight=0;
                attribute = object_node->first_attribute("height");
                if(attribute!=NULL)
                    objectHeight = atoi(attribute->value());

                int objectWidth=0;
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
                xml_node<>* polygon_node = object_node->first_node("polygon");
                vector<sf::Vector2i> points;
                if(polygon_node) {
                    string pointString;
                    attribute = polygon_node->first_attribute("points");
                    if(attribute!=NULL) {
                        pointString = attribute->value();
                        cout << pointString << endl;
                        istringstream iss(pointString);
                        string s;
                        //Splits every pair
                        while ( getline( iss, s, ' ' )) {
                            istringstream iss2(s);
                            //Gets the x coord
                            string t;
                            getline( iss2, t, ',' );
                            int x = atoi(t.c_str());
                            //gets the y coord
                            int y;
                            iss2 >> y;
                            points.push_back(sf::Vector2i(x,y));
                        }
                    }

                }


                xml_node<>* polyline_node = object_node->first_node("polyline");
                if(polyline_node) {
                    string pointString;
                    cout << pointString << endl;
                    attribute = polyline_node->first_attribute("points");
                    if(attribute!=NULL) {
                        pointString = attribute->value();
                        istringstream iss(pointString);
                        string s;
                        //Splits every pair
                        while ( getline( iss, s, ' ' )) {
                            istringstream iss2(s);
                            //Gets the x coord
                            string t;
                            getline( iss2, t, ',' );
                            int x = atoi(t.c_str());
                            //gets the y coord
                            int y;
                            iss2 >> y;
                            points.push_back(sf::Vector2i(x,y));
                        }
                    }
                }

                xml_node<>* ellipse_node = object_node->first_node("ellipse");

                ///****************************************************///
                ///        ADD STUFF HERE TO HAVE IT GET LOADED        ///
                /// SIMPLY ADDING A SCRIPT TO THE PROJECT ISN'T ENOUGH ///
                ///****************************************************///
                unsigned int id = ComponentBase::getNewID(); //Prefetches ID
                Entity* entity = new Entity(id);

                ///Commonly used options
                if(objectName!="none" || type!="none") //Adds a name, if needed
                    entity->setIdentification(std::make_shared<IDComponent>(objectName, type));
                if (objProperties.find("target") != objProperties.end()) //Adds a target, if needed
                    entity->setTarget(std::make_shared<TargetComponent>(objProperties["target"]));
                if (objProperties.find("script") != objProperties.end()) { //Adds a script, if needed
                    string script = objProperties["script"]; //ADD MORE SCRIPTS TO THIS PART
                    stringstream ss(script);
                    string s;

                    while (getline(ss, s, ',')) {
                        if(s=="camera") {
                            entity->addScript(std::make_shared<Camera>(width, height));
                        }
                        else if(s=="teleport") {
                            entity->addScript(std::make_shared<TeleportScript>());
                        }
                        else if(s=="explode") {
                            entity->addScript(std::make_shared<ExplodeScript>());
                        }
                        //if(script=="BLAHBLAHBLAH")
                    }
                }
                if (objProperties.find("movement") != objProperties.end()) {
                    string movement = objProperties["movement"];
                    if(movement=="pathfollow")
                        entity->setMovement(std::make_shared<PathFollowMovement>());
                }

                ///Modify position based on what it is
                if(objGid!=0)
                {
                    objectX +=sprites[objGid].getGlobalBounds().width/2;
                    objectY -=sprites[objGid].getGlobalBounds().height/2;
                }
                else if(objectHeight!=0 && objectWidth!=0) { //Has width and height, use that
                    objectX +=objectWidth/2;
                    objectY +=objectHeight/2;
                }
                //otherwise, don't change it

                ///Types!!
                if(type=="sensor" || type=="ladder" || type=="kill" || type=="guideline")
                { //Has physics box, but not collision. Can have script. Also ladder as it's special but similar

                    //Position
                    entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(objectX, objectY), layerNum));
                    //Physics Loading
                    if(ellipse_node) {
                        entity->setPhysics(std::make_shared<EllipsePhysics>(id, Vector2f(objectWidth, objectHeight), 0, PhysicsOptions::sensor | PhysicsOptions::isStatic, entity->getPosition()));
                    }
                    else if(polygon_node) {
                        entity->setPhysics(std::make_shared<PolygonPhysics>(id, points, PhysicsOptions::sensor | PhysicsOptions::isStatic, entity->getPosition()));
                    }
                    else if(polyline_node) {
                        entity->setPhysics(std::make_shared<PolylinePhysics>(id, points, PhysicsOptions::sensor | PhysicsOptions::isStatic, entity->getPosition()));
                    }
                    else {
                        entity->setPhysics(std::make_shared<SimpleBoxPhysics>(id, Vector2f(objectWidth, objectHeight), 0, PhysicsOptions::sensor | PhysicsOptions::isStatic | PhysicsOptions::sideSensors, entity->getPosition()));
                    }

                    if(type=="kill") {
                        entity->addScript(std::make_shared<KillScript>(false));
                    }

                }
                else if(type=="kinematic")
                {
                    entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(objectX, objectY), layerNum));
                    //Physics Loading
                    if(ellipse_node) {
                        entity->setPhysics(std::make_shared<EllipsePhysics>(id, Vector2f(objectWidth, objectHeight), 0, PhysicsOptions::isKinematic, entity->getPosition()));
                    }
                    else if(polygon_node) {
                        entity->setPhysics(std::make_shared<PolygonPhysics>(id, points, PhysicsOptions::isKinematic, entity->getPosition()));
                    }
                    else if(polyline_node) {
                        entity->setPhysics(std::make_shared<PolylinePhysics>(id, points, PhysicsOptions::isKinematic, entity->getPosition()));
                    }
                    else {
                        entity->setPhysics(std::make_shared<SimpleBoxPhysics>(id, Vector2f(objectWidth, objectHeight), 0, PhysicsOptions::isKinematic| PhysicsOptions::sideSensors, entity->getPosition()));
                    }

                    if(objGid!=0)
                        entity->setRender(std::make_shared<StaticSpriteComponent>(sprites[objGid]));
                }
                else if(type=="target") { //Only has world position component
                    entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(objectX, objectY), layerNum));
                }
                else if(type=="script") {//Only script and target
                    //No further loaded is needed, covered by common loaders
                }
                else if(type=="clutter") {
                    //Position
                    entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(objectX, objectY), layerNum));
                    //Physics Loading
                    if(objGid!=0)
                        entity->setPhysics(std::make_shared<SimpleBoxPhysics>(id, Vector2f(sprites[objGid].getGlobalBounds().width, sprites[objGid].getGlobalBounds().height), 1, 0x00, entity->getPosition()));
                    //Sprite
                    entity->setRender(std::make_shared<StaticSpriteComponent>(sprites[objGid]));

                }
                else if(type=="spawner") {
                    //Position
                    entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(objectX, objectY), layerNum));
                    int waitTime = 2;
                    int numToSpawn = 5;
                    int minDistance = 800;
                    if (objProperties.find("waitTime") != objProperties.end())
                        waitTime = atoi(objProperties["waitTime"].c_str());
                    if (objProperties.find("numToSpawn") != objProperties.end())
                        numToSpawn = atoi(objProperties["numToSpawn"].c_str());
                    if (objProperties.find("minDistance") != objProperties.end())
                        minDistance = atoi(objProperties["minDistance"].c_str());

                    entity->addScript(std::make_shared<EnemySpawner>(sprites[objGid], sf::seconds(waitTime), numToSpawn, minDistance));
                }
                else if(type=="mob") { //any sort of enemy, player, etc. Has everything basically
                    if (objProperties.find("type") != objProperties.end()) { //Adds a target, if needed
                        string mobType = objProperties["type"];
                        string mobName = objProperties["name"];
                        std::cout<<mobType<<std::endl;
                        entity->setPosition(std::make_shared<WorldPositionComponent>(Vector2f(objectX, objectY), layerNum));
                        if(mobType=="Samus") {
                            std::shared_ptr<BraveAdventurerAnimatedComponent> testSprite = std::make_shared<BraveAdventurerAnimatedComponent>();
                            SpriteManager spriteMan;

                            testSprite->setSprite(spriteMan.getSprite("Samus"));

                            entity->setRender(testSprite);

                            entity->setInput(std::make_shared<KeyboardInput>());

                            entity->setMovement(std::make_shared<BraveAdventurerMovement>());

                            entity->setPhysics(std::make_shared<SimpleBoxPhysics>(id,Vector2f(34,42),0, PhysicsOptions::roundedCorners | PhysicsOptions::notRotatable | PhysicsOptions::sideSensors, entity->getPosition()));
                            entity->setAudio(std::make_shared<AudioComponent>());
                            entity->setStats(std::make_shared<StatsComponent>(50, 50));
                            entity->addScript(std::make_shared<MainCharScript>(true, sf::seconds(2.5f)));
                            if(entity->getIdentification()!=nullptr)
                                entity->getIdentification()->setFaction("player");
                            else
                                entity->setIdentification(std::make_shared<IDComponent>(objectName, type, "player"));
                        }
                        else if(mobType=="enemy") {
                            SpriteManager spriteMan;
                            std::shared_ptr<BraveAdventurerAnimatedComponent> testSprite = std::make_shared<BraveAdventurerAnimatedComponent>();
                            testSprite->setSprite(spriteMan.getSprite("Samus"));
                            entity->setRender(testSprite);

                            entity->setMovement(std::make_shared<BraveAdventurerMovement>());
                            entity->setInput(std::make_shared<BasicAIInput>());
                            entity->setStats(std::make_shared<StatsComponent>(20));
                            entity->getStats()->setSpeed(.5);
                            entity->addScript(std::make_shared<MainCharScript>(false, sf::seconds(.5)));
                            entity->addScript(std::make_shared<KillScript>(false, 10, sf::seconds(.5)));
                            entity->setAudio(std::make_shared<AudioComponent>());
                            if(entity->getIdentification()!=nullptr)
                                entity->getIdentification()->setFaction("enemy");
                            else
                                entity->setIdentification(std::make_shared<IDComponent>(objectName, type, "enemy"));

                            entity->setPhysics(std::make_shared<SimpleBoxPhysics>(id,sf::Vector2f(34,42),0, PhysicsOptions::roundedCorners | PhysicsOptions::notRotatable | PhysicsOptions::sideSensors, entity->getPosition()));
                        }
                    }
                    else
                        throw runtime_error("No type associated with mob!");
                }

                //Adds a hurt value
                if (objProperties.find("hurt") != objProperties.end())
                {
                    string hurtStr = objProperties["hurt"];
                    int hurtVal = atoi(hurtStr.c_str());
                    entity->addScript(std::make_shared<KillScript>(false, hurtVal, (hurtVal!=-1) ? sf::seconds(.5) : sf::Time::Zero));
                }


                ComponentManager::getInst().addEntity(id, entity);
            }
        }
        layerNum++;
    } //every layer
    rendEng->resizeViews(sf::Vector2i(rendEng->window.getSize()));
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
