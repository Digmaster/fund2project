#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <SFML/System/Time.hpp>
#include <string>
#include <deque>

class ComponentManager; //Forward declaration
class RenderEngine;
class GameEngine;

class ComponentBase {
    public:
        /** Constructors */
        ComponentBase() : ID(0) {}
        ComponentBase(unsigned int ID) : ID(ID) {}
        ~ComponentBase() {}

        void setID(unsigned int ID) { this->ID = ID; }
        unsigned int getID() { return ID; }

        static unsigned int getNewID();

        void sendMessage(std::string input) {messages.push_back(input);}
        std::string getMessage();

        virtual void go(sf::Time) {}

        static void setRenderEngine(RenderEngine* RE) {rendEng = RE;}
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
