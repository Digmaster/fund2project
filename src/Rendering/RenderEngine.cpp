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
	addLayer(99,1,0); //Layer used for physics debug, with 1 zoom as hopefully high enough layer to be on the forefront

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
    for(map<int, layerStruct>::iterator it = layerList.begin(); it!=layerList.end(); it++) {
        window.setView(it->second.view);
        while(it->second.renderList.size() > 0) {
            window.draw(*it->second.renderList.back());
            it->second.renderList.pop_back();
        }
    }
    if(debugEnabled) {
        window.setView(layerList[99].view); //99 is the physics debug view. Don't mess with it.
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
        if(!it->second.noMove)
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

void RenderEngine::setLayerMove(int layer, bool noMove)
{
    layerList[layer].noMove = noMove;
}

void RenderEngine::addLayer(int layer, float zoom, bool noMove)
{
    layerList[layer].view.reset(FloatRect(0,0,screenWidth, screenHeight));
    layerList[layer].zoom = zoom;
    layerList[layer].view.zoom(zoom);
    layerList[layer].noMove = noMove;
}


void RenderEngine::toggleDebug() {
    cout << "Debug mode toggled" << endl;
    debugEnabled = !debugEnabled;
}
