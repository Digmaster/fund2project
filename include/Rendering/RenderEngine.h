#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "Components/Render/RenderComponent.h"
#include "Options.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include <map>
class AnimatedSprite;
class PhysicsEngine;

struct layerStruct {
    float zoom;
    std::deque<sf::Drawable*> renderList;
    sf::View view;
    layerStruct() : zoom(1) {}
};

class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();
        void render(sf::Time frameTime, PhysicsEngine*);
        void addSprite(sf::Drawable* input, int layer = 0);
        void addScreenSprite(sf::Drawable* input);
        void removeSprite(sf::Drawable* input, int layer);
        void removeScreenSprite(sf::Drawable* input);
        void flush() {layerList.clear();}
        void setBackgroundColor(sf::Color input) {bkColor = input;}
        void toggleDebug();
        void centerViews(sf::Vector2f);
        void zoomViews(float);
        void resizeViews(sf::Vector2i);
        void resetViews();
        void setLayerZoom(int, float);
        void addLayer(int, float = 1);
        sf::RenderWindow window;
    protected:
    private:
        bool debugEnabled;
        sf::Color bkColor;

        int screenWidth;
        int screenHeight;

        std::map<int, layerStruct> layerList;
        std::deque<sf::Drawable*> screenRenderList;
};

#endif // RENDERENGINE_H
