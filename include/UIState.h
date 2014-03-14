#ifndef UISTATE_H
#define UISTATE_H

#include <SFML/Graphics.hpp>
#include <deque>

class UIState
{
    public:
        /** Default constructor */
        virtual UIState() = 0;
        /** Default destructor */
        virtual ~UIState() = 0;
        virtual void stop() = 0;
        virtual void start() = 0;
        virtual void draw(sf::RenderWindow* win) = 0;
    protected:
    private:
};

#endif // UISTATE_H
