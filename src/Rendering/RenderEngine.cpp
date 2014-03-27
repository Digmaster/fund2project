#include "Rendering/RenderEngine.h"
#include "physics/PhysicsEngine.h"

using namespace sf;
using namespace std;

RenderEngine::RenderEngine() {
	ComponentBase::setRenderEngine(this); //Set this as the RenderEngine for the sprites
	int screenWidth = atoi(Options::instance().get("screen_width").c_str());
	int screenHeight = atoi(Options::instance().get("screen_height").c_str());
	int screenBBP = atoi(Options::instance().get("screen_bbp").c_str());
	int maxFPS = atoi(Options::instance().get("maxFPS").c_str());
    window.create(sf::VideoMode(screenWidth, screenHeight, screenBBP), "Fund2 Engine");
	window.setFramerateLimit(maxFPS);

	view.reset(FloatRect(0,0,screenWidth, screenHeight));

	bkColor = sf::Color::Black;
	debugEnabled = false;
	//view.zoom(.5);
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
	ComponentBase::setRenderEngine(NULL); //Sets rendering engine to NULL
}

void RenderEngine::render(sf::Time frameTime, PhysicsEngine* physEng) {
    window.setView(view);
    window.clear(bkColor);
    for(int i = 1; i <= renderList.size(); i++) {
        while(renderList[i].size() > 0) {
            window.draw(*renderList[i].back());
            renderList[i].pop_back();
        }
    }
    if(debugEnabled) {
        physEng->debugDraw();
    }
    window.display();
}

void RenderEngine::removeSprite(Drawable* input, int layer) {
    deque<Drawable*>::iterator it = find(renderList[layer].begin(), renderList[layer].end(), input);
    if(it != renderList[layer].end())
        renderList[layer].erase(it);
}

void RenderEngine::addSprite(Drawable* input, int layer) {
    renderList[layer].push_back(input);\
}

void RenderEngine::toggleDebug() {
    cout << "Debug mode toggled" << endl;
    debugEnabled = !debugEnabled;
}
