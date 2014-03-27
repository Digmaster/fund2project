#include "Components/Input/BraveAdventurerInput.h"
#include "Components/Movement/MovementComponent.h"
#include "Components/ComponentManager.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

BraveAdventurerInput::BraveAdventurerInput()
{
    //ctor
}

BraveAdventurerInput::~BraveAdventurerInput()
{
    //dtor
}

/*void BraveAdventurerInput::func(){
    // this function is started when thread.launch() is called
    sf::SoundBuffer buffer;
    if(buffer.loadFromFile("assets/art/sound.ogg")){
        sf::Sound SFX(buffer);
        SFX.setBuffer(buffer);
        cout<<"play sound?"<<endl;
        SFX.play();
        while(SFX.getStatus() == sf::Sound::Playing){}

    }
}
*/
void BraveAdventurerInput::go(sf::Time) {
    MovementComponent* movement = ComponentManager::getInst().moveSym.getComponent(getID());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement->sendMessage("WalkLeft");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
		movement->sendMessage("WalkRight");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
       /* sf::Thread thread(&func);
        thread.launch();*/
        movement->sendMessage("Jump");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        movement->sendMessage("GoPlace");
	}
}

