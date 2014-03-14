#include "UIEngine.h"

UIEngine::UIEngine()
{
    currState = &mainMenu;
}

UIEngine::~UIEngine()
{
    //dtor
}

void UIEngine::draw() {
    currState->draw();
}

void UIEngine::setState(UIStates input) {
    UIState* newState;
    switch input {
    case MAIN_MENU:
        newState = &mainMenu;
        break;
    case PAUSE_MENU:
        newState = &pauseMenu;
        break;
    case GAME_SCREEN:
        newState = &gameScreen;
        break;
    }
    if(newState!=currState) {
        currState->stop();
        currState = newState;
        currState->start();
    }
}
