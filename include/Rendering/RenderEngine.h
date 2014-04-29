#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "Components/Render/RenderComponent.h"
#include "Options.h"
#include <SFML/Graphics.hpp>
#include <deque>
#include <map>
class AnimatedSprite;
class PhysicsEngine;

///Contains all pertinent information about a layer
struct layerStruct {
    float zoom;
    std::deque<sf::Drawable*> renderList;
    sf::View view;
    layerStruct() : zoom(1) {}
    bool noMove;
};

//! Holds all information needed for rendering and renders frames
class RenderEngine
{
    public:
        //! Default constructor
        /*! Loads necessary information to initialize window from Options class */
        RenderEngine();
        //! Default deconstructor
        ~RenderEngine();
        //! Renders a frame
        /*! Renders all drawables added to the renderLists
            \param frameTime Time since last render (Currently not used for anything)
            \param pe Pointer to the Physics Engine, used for drawing physics debug information */
        void render(sf::Time frameTime, PhysicsEngine* pe);
        //! Adds a sprite to the layer's render list
        /*! Will be stored until the screen is rendered, then it must be readded. In essence, every frame you want something added, add it.
            This behavior may change in the future
            \param input Pointer to sf::Drawable to add
            \param layer Layer to draw it with */
        void addSprite(sf::Drawable* input, int layer = 0);
        //! Adds the sprite to the special screen sprite list.
        /*! Will be changed to use the special "RE::screenLayer" rendering layer in the future
            \param input Drawable to add to list */
        void addScreenSprite(sf::Drawable* input);
        //! Removes a sprite from the specified layer
        /*! This is mostly used to ensure a pointer does not exist to a non-existant sprite,
            in the rare case of an object is destroyed between the update of it's rendering component and render
            \param input Pointer to remove
            \param layer Layer thi Drawable exists in*/
        void removeSprite(sf::Drawable* input, int layer);
        //! Removes a sprite to the special screen sprite list.
        /*! Will be changed to use the special "RE::screenLayer" rendering layer in the future
            \param input Drawable to remove from the list */
        void removeScreenSprite(sf::Drawable* input);
        //! Clears all layerlists
        void flush() {layerList.clear();}
        //! Sets the background color of the screen
        /*! This will be the color that's displayed where ever a sprite does not cover the screen
            \param input sf::Color to set the background color too */
        void setBackgroundColor(sf::Color input) {bkColor = input;}
        //! Toggles if physics debug is shown or not
        void toggleDebug();
        //! Centers all non-static views to a point
        /*! \param center The point to center the views on */
        void centerViews(sf::Vector2f center);
        //! Modifies the zoom of all views, preserving the original zoom of each
        /*! /param float Multiplies the height and width of all views by this number. Thus a zoom of 2 shows 4 times as much of the screen */
        void zoomViews(float);
        //! Resizes all views to the same size, preserving the zoom of each view
        void resizeViews(sf::Vector2i);
        //! Resizes all views to the size of the window, preserving zoom
        void resetViews();
        //! Sets a specific layer's zoom
        void setLayerZoom(int layer, float zoom);
        //! Sets if a view is static or not
        /*! This currently doesn't work for unknown reasons
            \param layer the layer to modify
            \param moves set if the view moves or not */
        void setLayerMove(int layer, bool moves);
        //! Initializes a layer to inputted values, not technically needed
        /*! \param layer The layer's number
            \param zoom The zoom of the layer
            \param isStatic If the layer moves or not */
        void addLayer(int layer, float zoom = 1, bool isStatic = false);
        //! Pointer to the window that everything is rendered to
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
