#include "RenderEngine.h"

using namespace sf;

RenderEngine::RenderEngine() {
	AnimatedSprite::setRendEngine(this); //Set this as the RenderEngine for the sprites
	int screenWidth = atoi(Options::instance().get("screen_width").c_str());
	int screenHeight = atoi(Options::instance().get("screen_height").c_str());
	int screenBBP = atoi(Options::instance().get("screen_bbp").c_str());
	int maxFPS = atoi(Options::instance().get("maxFPS").c_str());
    window.create(sf::VideoMode(screenWidth, screenHeight, screenBBP), "Fund2 Engine");
    window.setFramerateLimit(maxFPS);
    rendList = new RenderList();
}

RenderEngine::~RenderEngine() {
	//dtor
}

void RenderEngine::render() {
    window.clear();
    for(deque<AnimatedSprite*>::iterator it = rendList->renderList.begin(); it != rendList->renderList.end(); it++) {
        try{ window.draw(**it); }
        catch(exception& e) {
            cout << e.what();
        }
    }
    window.display();
}
