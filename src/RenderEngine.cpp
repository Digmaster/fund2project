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

	view.reset(FloatRect(0,0,screenWidth, screenHeight));
}

RenderEngine::~RenderEngine() {
	AnimatedSprite::setRendEngine(NULL); //Sets rendering engine to NULL
}

void RenderEngine::render(sf::Time frameTime) {
    window.setView(view);
    window.clear();
    for(deque<AnimatedSprite*>::iterator it = renderList.begin(); it != renderList.end(); it++) {
        (*it)->update(frameTime);
        window.draw(**it);
    }
    window.display();
}

void RenderEngine::removeSprite(AnimatedSprite* input) {
    deque<AnimatedSprite*>::iterator it = find(renderList.begin(), renderList.end(), input);
    if(it != renderList.end())
        renderList.erase(it);
}

void RenderEngine::addSprite(AnimatedSprite* input) {
    if(input!=NULL && find(renderList.begin(), renderList.end(), input)==renderList.end()) //Makes sure sprite dosen't already exist on list, to avoid double rendering
        renderList.push_back(input);\
}
