#include "Rendering/RenderEngine.h"
#include "physics/PhysicsEngine.h"

using namespace sf;
using namespace std;

RenderEngine::RenderEngine() {
	ComponentBase::setRenderEngine(this); //Set this as the RenderEngine for the sprites
    screenWidth = atoi(Options::instance().get("screen_width").c_str());
	screenHeight = atoi(Options::instance().get("screen_height").c_str());
	int screenBBP = atoi(Options::instance().get("screen_bbp").c_str());
	int maxFPS = atoi(Options::instance().get("maxFPS").c_str());
    window.create(sf::VideoMode(screenWidth, screenHeight, screenBBP), "Fund2 Engine");
	window.setFramerateLimit(maxFPS);

	//view.reset(FloatRect(0,0,screenWidth, screenHeight));

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
    window.clear(bkColor);
    for(int i = 1; i <= layerList.size(); i++) {
        window.setView(layerList[i].view);
        while(layerList[i].renderList.size() > 0) {
            window.draw(*layerList[i].renderList.back());
            layerList[i].renderList.pop_back();
        }
    }
    if(debugEnabled) {
        physEng->debugDraw();
    }
    window.display();
}

void RenderEngine::removeSprite(Drawable* input, int layer) {
/*    deque<Drawable*>::iterator it = find(renderList[layer].begin(), renderList[layer].end(), input);
    if(it != renderList[layer].end())
        renderList[layer].erase(it);*/
}

void RenderEngine::addSprite(Drawable* input, int layer) {
    layerList[layer].renderList.push_back(input);
    //renderList[layer].push_back(input);
}

void RenderEngine::centerViews(sf::Vector2f center)
{
    for(map<int, layerStruct>::iterator it = layerList.begin(); it!=layerList.end(); it++) {
        it->second.view.setCenter(center.x, center.y);
    }
}

void RenderEngine::zoomViews(float)
{

}

void RenderEngine::resizeViews(sf::Vector2i size)
{
    for(map<int, layerStruct>::iterator it = layerList.begin(); it!=layerList.end(); it++) {
        it->second.view.setSize(size.x, size.y);
        it->second.view.zoom(it->second.zoom);
    }
}

void RenderEngine::resetViews() {
    resizeViews(sf::Vector2i(screenWidth, screenHeight));
}

void RenderEngine::setLayerZoom(int layer, float zoom)
{
    layerList[layer].zoom = zoom;
}

void RenderEngine::addLayer(int layer, float zoom)
{
    layerList[layer].view.reset(FloatRect(0,0,screenWidth, screenHeight));
    layerList[layer].zoom = zoom;
    layerList[layer].view.zoom(zoom);
}


void RenderEngine::toggleDebug() {
    cout << "Debug mode toggled" << endl;
    debugEnabled = !debugEnabled;
}
