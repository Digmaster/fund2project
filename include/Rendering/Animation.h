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
// SOURCE: https://github.com/LaurentGomila/SFML/wiki/Source%3A-AnimatedSprite
//
////////////////////////////////////////////////////////////

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <stdexcept>

//! Contains all information to play an animation
/*! \see AnimatedSprite */
class Animation
{
public:
    //! Default constructor
    /*! \param frameTime the time to spend on each frame, in sf::seconds */
    Animation(sf::Time frameTime = sf::seconds(0.2f));
    //! Adds a frame
    /*! \param rect The texture rectangle of the frame */
    void addFrame(sf::IntRect rect);
    //! Sets the texture of the animation
    /*! Load through the TextureManager!!!
        \param texture sf::Texture to set animation to */
    void setSpriteSheet(const sf::Texture& texture);
    //! Gets the texture associated with the animation
    /*! /return Pointer to the sf::Texture */
    const sf::Texture* getSpriteSheet() const;
    //! Gets the size of the animation
    /*! Used to find number of frames in the animation
        \return The std::size_t of the animation */
    std::size_t getSize() const;
    //! Gets the frametime of the animation
    /*! \return The sf::Time of each frame */
    sf::Time getFrameTime() const;
    //! Sets the frametime of the animation
    /*! \param time The time of every frame, as a float vale */
    void setFrameTime(float);
    //! Gets a frame
    /*! \param n the frame number
        \return The sf::IntRect of the frame
    */
    const sf::IntRect& getFrame(std::size_t n) const;

private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture* m_texture;
    sf::Time m_frameTime;
};

#endif // ANIMATION_H
