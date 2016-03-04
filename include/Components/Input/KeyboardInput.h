#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include "Components/Input/InputComponent.h"
#include "InputEngine.h"

///Simply grabs the appropriate input information from the Input Engine
class KeyboardInput : public InputComponent
{
    public:
        KeyboardInput();
        virtual ~KeyboardInput();
        void go(sf::Time, Entity* entity);
    protected:
    private:
        void addKeyboardListener(KeyboardEvent event, InputEngine::keyboardListener listener);
        std::list<InputEngine::keyboardListenerList::iterator> subscribedEvents;
};

#endif // KEYBOARDINPUT_H
