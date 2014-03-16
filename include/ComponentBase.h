#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <SFML/System/Time.hpp>

class ComponentBase {
    public:
        /** Constructors */
        ComponentBase() : ID(0) {}
        ComponentBase(unsigned int ID) : ID(ID) {}
        /** Default destructor */
        ~ComponentBase() {}

        void setID(unsigned int ID) { this->ID = ID; }
        unsigned int getID() { return ID; }

        virtual void go(sf::Time) {};
    protected:
    private:
        unsigned int ID;
};

#endif // COMPONENTBASE_H
