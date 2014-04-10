#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <SFML/System/Time.hpp>
#include <string>
#include <deque>
#include <iostream>

class ComponentManager; //Forward declaration
class RenderEngine;
class GameEngine;

//! Base class of which all components are derived from
/*! Includes base functionality, but should never be instantiated alone */
class ComponentBase {
    public:
        /** Constructors */
        //! Default constructor
        /*! Sets the ID to the correct value
            \param ID Sets the ID of the object */
        ComponentBase(unsigned int ID = 0) : ID(ID) {}
        //! Default destructor
        ~ComponentBase() {std::cout << "Someone has killed a component! As I haven't made component clean up work yet, this is a big big fatass problem! Whatever you changed, fix it!" << std::endl;}


        //! Sets the ID
        /*! \param ID The unisgned int to set the value of this component's ID to */
        void setID(unsigned int ID) { this->ID = ID; }
        //! Returns the ID of the component
        /*! \return The Component's ID */
        unsigned int getID() { return ID; }

        //! Returns a new, unused ID
        static unsigned int getNewID();

        //! Sends a message to this component's message deque
        /*! \param input String to add to the message deque */
        void sendMessage(std::string input) {messages.push_back(input);}
        //! Gets the least recent message
        /*! Once gotten, this message will be removed from the deque
            \return The message */
        std::string getMessage();

        //! A function to update the component and do whatever the component is designed to do.
        /*! \param frameTime Difference in time between last update and this one */
        virtual void go(sf::Time frameTime) {}

        //! Sets the rendering engine
        /*! Will be depreciated in favor of all encompassing "GameEngine" pointer
            \see RenderEngine */
        static void setRenderEngine(RenderEngine* RE) {rendEng = RE;}
        //! Sets the GameEngine
        /*! \see GameEngine */
        static void setEngine(GameEngine* gameEng) {eng = gameEng;}
    protected:
        unsigned int ID;
        std::deque<std::string> messages;
        static ComponentManager* compMan;
        static RenderEngine* rendEng;
        static GameEngine* eng;
    private:
};

#endif // COMPONENTBASE_H
