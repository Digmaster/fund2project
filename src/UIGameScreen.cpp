#include "UIGameScreen.h"

UIGameScreen::UIGameScreen()
{
    SpriteManager.loadFile("UIElements.xml")
}

UIGameScreen::~UIGameScreen()
{
    //dtor
}

void UIGameScreen::draw(sf::RenderWindow* win) {

	//Draw the condition bars

	//Main
	AnimatedSprite spr = spriteMan.getSprite("HUDMain";
	sf::View view = win->getView();
	sf::Vector2u size = win->getSize();
	sf::IntRect rect = spr.getTextureRect();
	//Big condition bag part
	spr.setPosition(view.getCenter().x-size.x/2,view.getCenter().y-size.y/2);
	win->draw(spr);
	//draw health bars
	spr = spriteMan.getSprite("HUDTubeEmpty");
	int i;
	int healthWidth=spr.getTextureRect().width;
	for(i=0; i<3; i++) {
		spr.setPosition(view.getCenter().x-size.x/2+rect.width+(healthWidth)*i,view.getCenter().y-size.y/2+4);
		win->draw(spr);
	}
	spr = spriteMan.getSprite("HUDHealthEnd");
	spr.setPosition(view.getCenter().x-size.x/2+rect.width+(healthWidth)*i,view.getCenter().y-size.y/2+2);
	win->draw(spr);
	if(character->getWounds()>0) {
		spr = spriteMan.getSprite("HUDHealthStart");
		spr.setPosition(view.getCenter().x-size.x/2+rect.width,view.getCenter().y-size.y/2+6);
		win->draw(spr);
		spr = spriteMan.getSprite("HUDHealthMid");
		for(int i=1; i<character->getWounds(); i++) {
			spr.setPosition(view.getCenter().x-size.x/2+rect.width+(spr.getTextureRect().width)*i,view.getCenter().y-size.y/2+6);
			win->draw(spr);
		}
	}
}
