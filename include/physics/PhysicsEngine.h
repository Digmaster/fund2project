#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <SFML/System/Time.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Components/Render/DebugDraw.h"
#include <deque>

//! Stores all contact listeners and iterates through them whenever any objects collide
class ContactListener : public b2ContactListener {
public:
    //! Called by the physics engine, should not be used outside of the Box2D code
    void BeginContact(b2Contact* contact);
    //! Called by the physics engine, should not be used outside of the Box2D code
    void EndContact(b2Contact* contact);
    //! Adds a listener to the Contact Listener list
    /*! \param input pointer to the contact listener to add */
    void addListener(b2ContactListener* input);
    //! Removes a listener to the Contact Listener list
    /*! \param input pointer to the contact listener to remove */
    void removeListener(b2ContactListener* input);
private:
    std::deque< b2ContactListener* > listenerList;
};

//! Contains all information relevant to physics simulation
class PhysicsEngine
{
    public:
        //! Defalut constructor
        PhysicsEngine();
        //! Default destructor
        ~PhysicsEngine();
        //! Advances the physics simulation
        /*! \param deltaTime the time difference between now and the previous physics step */
        void step(sf::Time deltaTime);
        //! Function called by rendering engine to draw debug boxes around all physics entities
        void debugDraw();
        //! Creates the debug draw
        /*! \param rendWindow The sf::RenderingWindow used in the program */
        void setDebugDraw(sf::RenderWindow& rendWindow);
        //! Initializes the physics engine
        void init();
        //! The list of contact listeners
        ContactListener contactListeners;
        //! The physics world
        b2World* _world;
    protected:
    private:
        int _velocityIterations;
        int _positionIterations;
};

#endif // PHYSICSENGINE_H
