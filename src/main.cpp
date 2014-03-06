#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include <iostream>
#include <fstream>
#include <string>
#include "TextureManager.h"
#include "SpriteManager.h"
#include "RenderEngine.h"

using namespace std;
using namespace sf;


int main()
{
    RenderEngine rendEng;
    SpriteManager spriteMan;
    spriteMan.loadFile("assets/testSprite.xml");
    spriteMan.loadFile("assets/SamusSprites.xml");
    AnimatedSprite animatedSprite = spriteMan.getSprite("Samus");

    // set up AnimatedSprite
    animatedSprite.setPosition(sf::Vector2f(0, 0));
    animatedSprite.setAnimation("WalkDown");

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    while (rendEng.window.isOpen())
    {
        sf::Event event;
        while (rendEng.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rendEng.window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                rendEng.window.close();
            if (event.type == sf::Event::Resized)
                rendEng.view.setSize(event.size.width, event.size.height);
        }

        sf::Time frameTime = frameClock.restart();


        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        std::string currAnimation;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            //currentAnimation = &walkingAnimationUp;
            currAnimation="Dissipate";
            //movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            //currentAnimation = &walkingAnimationDown;
            currAnimation="WalkDown";
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            //currentAnimation = &walkingAnimationLeft;
            currAnimation="WalkLeft";
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            //currentAnimation = &walkingAnimationRight;
            currAnimation="WalkRight";
            movement.x += speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            rendEng.view.zoom(.99);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            rendEng.view.zoom(1.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
        {
            rendEng.view.rotate(-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
        {
            rendEng.view.rotate(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
        {
            rendEng.view.move(0,-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        {
            rendEng.view.move(0,1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
        {
            rendEng.view.move(-1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
        {
            rendEng.view.move(1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
        {
            rendEng.view.setRotation(0);
        }
        animatedSprite.setAnimation(currAnimation);
        animatedSprite.play();
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        //rendEng.window.clear();
        rendEng.render();
        //rendEng.window.draw(animatedSprite);
        //rendEng.window.display();
        /*window.clear();
        window.draw(animatedSprite);
        window.display(); */
    }

    return 0;
}
