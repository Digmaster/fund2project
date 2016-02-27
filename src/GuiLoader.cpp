#include "GuiLoader.h"
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

GuiLoader::GuiLoader()
{
    texMan = new TextureManager();
}

using namespace std;
using namespace sf;
using namespace rapidxml;


void GuiLoader::load(std::string filename, GameEngine* eng)
{
    xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	ifstream file(filename);
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

    int GUI_LAYER = 100;
    eng->rendEng->addLayer(GUI_LAYER, 1, true);

    for (xml_node<>* gui_node = doc.first_node("gui"); gui_node; gui_node = gui_node->next_sibling()) {
        std::string guiName = gui_node->first_attribute("name")->value();
        std::string guiLocation = gui_node->first_attribute("location")->value();
        for (xml_node<>* element_node = gui_node->first_node(); element_node; element_node = element_node->next_sibling()) {
            std::string name = element_node->name();

            int ID = ComponentManager::getNewID();
            Entity* entity = new Entity(ComponentManager::getNewID());

            std::string position = "0,0";
            auto xmlAttribute = element_node->first_attribute("position");
            if(xmlAttribute!=nullptr)
                position = xmlAttribute->value();

            stringstream ss(position);
            string s;
            getline( ss, s, ',' );
            int x = atoi(s.c_str());
            getline( ss, s, ',' );
            int y = atoi(s.c_str());
            sf::Vector2f pos(x,y);

            entity->setPosition(std::make_shared<WorldPositionComponent>(pos, GUI_LAYER));

            string itemName = "";
            xmlAttribute = element_node->first_attribute("name");
            if(xmlAttribute!=nullptr)
                itemName = xmlAttribute->value();

            if(name=="text")
            {
                std::string value = element_node->first_attribute("value")->value();

                std::string listenTo = "MainChar";
                auto listenToXml = element_node->first_attribute("listenTo");
                if(listenToXml!=nullptr)
                    listenTo = listenToXml->value();

                int textSize = 30;
                listenToXml = element_node->first_attribute("textSize");
                if(listenToXml!=nullptr)
                    textSize = atoi(listenToXml->value());

                entity->setTarget(std::make_shared<TargetComponent>(listenTo));
                entity->setRender(std::make_shared<TextComponent>(ThingsToWatch::health, textSize, sf::Color::Yellow));
            }

            ComponentManager::getInst().addEntity(ID, entity);

        }
    }
    eng->rendEng->resizeViews(sf::Vector2i(eng->rendEng->window.getSize()));
}
