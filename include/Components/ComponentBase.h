#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <SFML/System/Time.hpp>
#include <string>
#include <deque>

class ComponentBase {
    public:
        /** Constructors */
        ComponentBase() : ID(0) {}
        ComponentBase(unsigned int ID) : ID(ID) {}
        ~ComponentBase() {}

        void setID(unsigned int ID) { this->ID = ID; }
        unsigned int getID() { return ID; }

        void sendMessage(std::string input) {messages.push_back(input);}
        std::string getMessage();

        virtual void go(sf::Time) {}
    protected:
        unsigned int ID;
        std::deque<std::string> messages;
    private:
};

#endif // COMPONENTBASE_H
