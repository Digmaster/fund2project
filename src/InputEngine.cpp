#include "InputEngine.h"
#include "GameEngine.h"
#include "Rendering/RenderEngine.h"

InputEngine::InputEngine()
{
    eng = NULL;
    walkLeft=false;
    walkRight=false;
    climbUp=false;
    climbDown=false;
    activate=false;
    fire=false;
    jump=false;
    currWeapon=0;
    mousePos = sf::Vector2f(0,0);

    Options opt = Options::instance();
    keyAction[opt.getInt("up")] = [=](int, bool pressed) mutable {climbUp = pressed;};
    keyAction[opt.getInt("down")] = [=](int, bool pressed) mutable {climbDown = pressed;};
    keyAction[opt.getInt("left")] = [=](int, bool pressed) mutable {walkLeft = pressed;};
    keyAction[opt.getInt("right")] = [=](int, bool pressed) mutable {walkRight = pressed;};
    keyAction[opt.getInt("jump")] = [=](int, bool pressed) mutable {jump = pressed;};
}

InputEngine::~InputEngine()
{
    //dtor
}

void InputEngine::update(GameEngine* eng)
{
    this->eng=eng;
    sf::Event event;
    while(eng->rendEng->window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::KeyPressed:
            switch(event.key.code) {
            case sf::Keyboard::Escape:
                eng->rendEng->window.close();
                break;
            case sf::Keyboard::F2:
                eng->rendEng->toggleDebug();
                break;
            case sf::Keyboard::Equal:
                eng->rendEng->zoomViews(.9);
                break;
            case sf::Keyboard::Subtract:
                eng->rendEng->zoomViews(1.1);
                break;
            default:
                if(event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9)
                    currWeapon = event.key.code-sf::Keyboard::Num0;
                else if(keyAction.find(event.key.code)!=keyAction.end())
                    keyAction[event.key.code](event.key.code, true);
                break;
            }
            break;
        case sf::Event::KeyReleased:
            switch(event.key.code) {
            default:
                if(keyAction.find(event.key.code)!=keyAction.end())
                    keyAction[event.key.code](event.key.code, false);
            }
            break;
        case sf::Event::MouseButtonPressed:
            switch(event.mouseButton.button) {
            case sf::Mouse::Right:
                fire = true;
                break;
            case sf::Mouse::Left:
                fire = true;
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonReleased:
            switch(event.mouseButton.button) {
            case sf::Mouse::Right:
                fire = false;
                break;
            case sf::Mouse::Left:
                fire = false;
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseMoved:
            scrMousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            break;
        case sf::Event::Closed:
            eng->rendEng->window.close();
            break;
        case sf::Event::Resized:
            eng->rendEng->resizeViews(sf::Vector2i(event.size.width, event.size.height));
            break;
        case sf::Event::LostFocus:
            eng->pause();
            break;
        case sf::Event::GainedFocus:
            eng->unpause();
            break;
        default:
            break;
        }
    }
    mousePos = eng->rendEng->window.mapPixelToCoords(scrMousePos);
}



InputEngine::keyboardListenerList::iterator InputEngine::addListener(KeyboardEvent toListenTo, keyboardListener& toCall)
{
    componentListeners[toListenTo].push_back(toCall);
    return --componentListeners[toListenTo].end();
}

float InputEngine::getMouseAngle(sf::Vector2f position){
    float yDif = mousePos.y-position.y;
    float xDif = mousePos.x-position.x;
    if(xDif==0) xDif=.1;
    return atan2(yDif,xDif) * -180.0f/3.14159265f;
}
