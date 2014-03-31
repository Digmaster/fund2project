#include "InputEngine.h"
#include "GameEngine.h"
#include "Rendering/RenderEngine.h"

InputEngine::InputEngine()
{
    //ctor
}

InputEngine::~InputEngine()
{
    //dtor
}

void InputEngine::update(GameEngine* eng)
{
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
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            break;
        case sf::Event::Closed:
            eng->rendEng->window.close();
            break;
        case sf::Event::Resized:
            eng->rendEng->view.setSize(event.size.width, event.size.height);
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
}

float InputEngine::getMouseAngle(sf::Vector2f position){
    float xDif = position.x-mouseX;
    float yDif = position.y-mouseY;
    return atan(yDif/xDif) * 180.0f/3.14159265f;
}
