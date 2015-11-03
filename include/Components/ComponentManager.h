#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include <SFML/System/Time.hpp>
#include <iostream>

class Entity;

///Manages/contains all components
class ComponentManager
{
    public:
        /** Default destructor */
        virtual ~ComponentManager();


        void processAll(sf::Time frameTime);

        static unsigned int getNewID();

        void addEntity(int ID, Entity* entity);
        void removeEntity(int ID);

        static ComponentManager& getInst() {
            static ComponentManager INSTANCE;
            return INSTANCE;
        }

        unsigned int name2ID(std::string);

        Entity* operator[](unsigned int i) {
            if(entities.find(i)==entities.end())
            {
                return nullptr;
            }
            return entities[i];}
    protected:
        std::unordered_map<int, Entity*> entities;
    private:

};

#endif // COMPONENTMANAGER_H
