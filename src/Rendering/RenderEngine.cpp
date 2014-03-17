#include "Rendering/RenderEngine.h"

using namespace sf;
using namespace std;

RenderEngine::RenderEngine() {
	RenderComponent::setRenderEngine(this); //Set this as the RenderEngine for the sprites
	int screenWidth = atoi(Options::instance().get("screen_width").c_str());
	int screenHeight = atoi(Options::instance().get("screen_height").c_str());
	int screenBBP = atoi(Options::instance().get("screen_bbp").c_str());
	int maxFPS = atoi(Options::instance().get("maxFPS").c_str());
    window.create(sf::VideoMode(screenWidth, screenHeight, screenBBP), "Fund2 Engine");
	window.setFramerateLimit(maxFPS);

	view.reset(FloatRect(0,0,screenWidth, screenHeight));
}

void RenderEngine::addScreenSprite(sf::Drawable* input){
    screenRenderList.push_back(input);
}

void RenderEngine::removeScreenSprite(sf::Drawable* input){
    deque<Drawable*>::iterator it = find(screenRenderList.begin(), screenRenderList.end(), input);
    if(it != screenRenderList.end())
        screenRenderList.erase(it);
}

RenderEngine::~RenderEngine() {
	RenderComponent::setRenderEngine(NULL); //Sets rendering engine to NULL
}

void RenderEngine::render(sf::Time frameTime) {
    window.setView(view);
    window.clear();
    while(renderList.size() > 0) {
        window.draw(*renderList.back());
        renderList.pop_back();
    }
    window.display();
}

void RenderEngine::removeSprite(Drawable* input) {
    deque<Drawable*>::iterator it = find(renderList.begin(), renderList.end(), input);
    if(it != renderList.end())
        renderList.erase(it);
}

void RenderEngine::addSprite(Drawable* input) {
    renderList.push_back(input);\
}
