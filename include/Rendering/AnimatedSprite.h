////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// Source: https://github.com/LaurentGomila/SFML/wiki/Source%3A-AnimatedSprite
//
////////////////////////////////////////////////////////////

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Rendering/Animation.h"
#include <unordered_map>
#include "Rendering/RenderEngine.h"

class RenderEngine;

//! Animated sprite
/*! Draws a multi-frame sprite to the screen, along with managing all available animations for the sprite */
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
    //! Default constructor
    /*! Creates an animated sprite, initially with no associated animations
        \param speed The default speed to play animations. This modifies the animation's frame time (Defalut: 1)
        \param paused Sets if the animation should be initially paused (Default: false)
        \param looped Sets if the animation should be initially looped (Default: True)
    */
    explicit AnimatedSprite(float speed = 1, bool paused = false, bool looped = true);
        //AnimatedSprite(const AnimatedSprite &copyFrom); //Copy Constructor
        //AnimatedSprite& operator=( const AnimatedSprite& rhs );
    //! Default destructor
    /*! Destroys all loaded animations */
    ~AnimatedSprite();
    //! Updates the animation to show the correct frame
    /*! \param deltaTime the difference in time between the last update and this one */
    void update(sf::Time deltaTime);
    //! Sets the current Animation to one that's not currently loaded into the AnimatedSprite
    /*! \param animation Animation to play */
    void setAnimation(const Animation& animation);
    //! Sets the current Animation to a loaded Animation
    /*! \param animation The name of the animation to play (if it doesn't exist, current animation will continue) */
    void setAnimation(std::string animation);
    //! Adds an animation to the Animated Sprite
    /*! if animation already exists by this name it will be overwritten
        \param name The name of the Animation
        \param animation The animation to add
    */
    void addAnimation(std::string name, Animation& animation);
    //! Checks if an animation by name exists
    /*! \param name The name of the animation
        \return Bool, true if it exists, false if not
    */
    bool doesAnimationExist(std::string name);
    //! Sets the speed of the animation, which augments the frametime of all animations
    /*! A speed of 2 results in half the time spent on each frame
        \param input The speed to change to, a float value */
    void setSpeed(float input) {m_speed = input;}
    //! Returns the current speed of animation
    /*! \return the current speed, a float value */
    float getSpeed() {return m_speed;}
    //! Unpauses the animation, if currently paused
    void play();
    //! Plays a specific animation
    /*! /param animation The animation to play */
    void play(const Animation& animation);
    //! Pauses the animation
    void pause();
    //! Stops the animation, returning to the first frame
    void stop();
    //! Sets if the animation should loop
    /*! \param looped A bool to set "looped" to */
    void setLooped(bool looped);
    //! Sets the color mask
    /*! The color added will be multiplied by all colors of the sprite. A pure white color of half alpha will result in a half-transparent sprite
        \param color A sf::Color to multiply the sprite's colors by */
    void setColor(const sf::Color& color);
    //! Returns the currently playing animation
    /*! \return An animation of type Animation */
    const Animation* getAnimation() const;
    //! Returns the local bounds of the sprite
    /*! Returns the bounds of the sprite ignoring all transformations applied on the sprite
        \return The bounding rectangle of type sf::FloatRect */
    sf::FloatRect getLocalBounds() const;
    //! Returns the global bounds of the sprite
    /*! Returns the bounds of the sprite including all transformations applied on the sprite
        \return The bounding rectangle of type sf::FloatRect */
    sf::FloatRect getGlobalBounds() const;
    //! Returns whether the animation is set to loop or not
    /*! \return A bool value */
    bool isLooped() const;
    //! Returns whether the animation is currently playing or not
    /*! \return A bool value */
    bool isPlaying() const;
    //! Sets the frame to a specific value
    /*! \param newFrame The frame number to switch to
        \param resetTime Reset time spent on current frame or not (default: true)*/
    void setFrame(std::size_t newFrame, bool resetTime = true);
private:
    const Animation* m_animation;
    sf::Time m_currentTime;
    std::size_t m_currentFrame;
    bool m_isPaused;
    bool m_isLooped;
    const sf::Texture* m_texture;
    sf::Vertex m_vertices[4];
        std::unordered_map<std::string, Animation> animationMap;
        float m_speed;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif // ANIMATEDSPRITE_H
