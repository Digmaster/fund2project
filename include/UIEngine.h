#ifndef UIENGINE_H
#define UIENGINE_H

#include "UIState.h"
#include "UIGameScreen.h"

enum UIStates {
    MAIN_MENU,
    PAUSE_MENU,
    GAME_SCREEN
};

class UIEngine
{
    public:
        UIEngine();
        ~UIEngine();
        void draw();
        void setState(UIStates input);
    protected:
    private:
        UIState* currState;
//        UIMainMenu mainMenu;
//        UIPauseMenu pauseMenu;
//        UIGameScreen gameScreen;
};

#endif // UIENGINE_H
