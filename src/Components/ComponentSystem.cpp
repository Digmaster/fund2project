#include "Components/ComponentSystem.h"

template<class T>
void ComponentSystem<T>::process(sf::Time frameTime) {
    for(typename std::map<unsigned int, T* >::iterator it = components.begin(); it!=components.end(); it++) {
        assert((ComponentBase const*)&(*it));
        it->go(frameTime);
    }
}
