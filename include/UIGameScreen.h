#ifndef UIGAMESCREEN_H
#define UIGAMESCREEN_H

#include "UIState.h"


class UIGameScreen : public UIState
{
    public:
        /** Default constructor */
        UIGameScreen();
        /** Default destructor */
        ~UIGameScreen();
        void stop();
        void start();
        void draw(sf::RenderWindow* win);
    protected:
    private:
        TextureManager texMan;
        SpriteManager spriteMan;
};

#endif // UIGAMESCREEN_H
