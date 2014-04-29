#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H

#include <SFML/System/Time.hpp>
#include "Components/ComponentBase.h"
#include <cassert>
#include <map>

#include "Components/Render/RenderComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Components/Input/InputComponent.h"
#include "Components/Movement/MovementComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Identification/IDComponent.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Script/ScriptComponent.h"
#include "Components/Audio/AudioComponent.h"

using namespace std;

///Holds components of a specific type and runs them all at once
template <class T> class ComponentSystem
{
    public:
        ///Loops through all components and "go"s them
        void process(sf::Time);
        ///Adds a component
        void addComponent(T);
        ///Returns a component from ID
        T getComponent(unsigned int ID);
        ///Returns the number of components contained within
        int getSize();
        ///The components!
        std::map<unsigned int, T> components;
    protected:
    private:
};

template<class T>
void ComponentSystem<T>::process(sf::Time frameTime) {
    for(typename std::map<unsigned int, T>::iterator it = components.begin(); it!=components.end(); it++) {
        if(it->second->getID()!=0) {
            it->second->go(frameTime);
        }
    }
    //cout << getSize() << endl;
}

template<class T>
void ComponentSystem<T>::addComponent(T input) {
    components[input->getID()]=input;
}

template<class T>
T ComponentSystem<T>::getComponent(unsigned int ID) {
    typename map<unsigned int,T>::iterator it = components.find(ID);
    if(it!=components.end()) {
        return it->second;
    }
    else
        return NULL;
}

template<class T>
int ComponentSystem<T>::getSize() {
    return components.size();
}

#endif // COMPONENTSYSTEM_H
