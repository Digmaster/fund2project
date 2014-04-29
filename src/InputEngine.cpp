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
    mousePos = sf::Vector2f(0,0);
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
            case sf::Keyboard::W:
                climbUp = true;
                break;
            case sf::Keyboard::A:
                walkLeft = true;
                break;
            case sf::Keyboard::S:
                climbDown = true;
                break;
            case sf::Keyboard::D:
                walkRight = true;
                break;
            case sf::Keyboard::Space:
                jump = true;
                break;
            case sf::Keyboard::E:
                activate = true;
                break;
            case sf::Keyboard::Escape:
                eng->rendEng->window.close();
                break;
            case sf::Keyboard::F2:
                eng->rendEng->toggleDebug();
                break;
            default:
                break;
            }
            break;
        case sf::Event::KeyReleased:
            switch(event.key.code) {
            case sf::Keyboard::W:
                climbUp = false;
                break;
            case sf::Keyboard::A:
                walkLeft = false;
                break;
            case sf::Keyboard::S:
                climbDown = false;
                break;
            case sf::Keyboard::D:
                walkRight = false;
                break;
            case sf::Keyboard::Space:
                jump = false;
                break;
            case sf::Keyboard::E:
                activate = false;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            switch(event.mouseButton.button) {
            case sf::Mouse::Right:
                fire = true;
                std::cout<<"FIRE"<<std::endl;
                break;
            case sf::Mouse::Left:
                fire = true;
                std::cout<<"FIRE"<<std::endl;
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

float InputEngine::getMouseAngle(sf::Vector2f position){
    float yDif = mousePos.y-position.y;
    float xDif = mousePos.x-position.x;
    if(xDif==0) xDif=.1;
    return atan2(yDif,xDif) * -180.0f/3.14159265f;
}
