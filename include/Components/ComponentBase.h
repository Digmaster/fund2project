#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <SFML/System/Time.hpp>
#include <string>
#include <deque>
#include <iostream>

class ComponentManager; //Forward declaration
class RenderEngine;
class GameEngine;
class Entity;

//! Base class of which all components are derived from
/*! Includes base functionality, but should never be instantiated alone */
class ComponentBase {
    public:
        /** Constructors */
        //! Default constructor
        /*! Sets the ID to the correct value
            \param ID Sets the ID of the object */
        ComponentBase() {}

        virtual void setUpListeners(Entity*) {}


        //! Returns a new, unused ID
        static unsigned int getNewID();

        //! A function to update the component and do whatever the component is designed to do.
        /*! \param frameTime Difference in time between last update and this one */
        virtual void go(sf::Time frameTime,  Entity* entity) =0;

        //! Sets the rendering engine
        /*! Will be depreciated in favor of all encompassing "GameEngine" pointer
            \see RenderEngine */
        static void setRenderEngine(RenderEngine* RE) {rendEng = RE;}
        //! Sets the GameEngine
        /*! \see GameEngine */
        static void setEngine(GameEngine* gameEng) {eng = gameEng;}
    protected:
        unsigned int ID;
        static ComponentManager* compMan;
        static RenderEngine* rendEng;
        static GameEngine* eng;
    private:
};

#endif // COMPONENTBASE_H
