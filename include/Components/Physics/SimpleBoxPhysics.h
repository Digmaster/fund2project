#ifndef SIMPLEBOXPHYSICS_H
#define SIMPLEBOXPHYSICS_H

#include "Components/ComponentManager.h"
#include "Components\Physics\PhysicsComponent.h"

#include "Components\Identification\IDComponent.h"

#include "Components/EventDefines.h"


class FootContactListener;
class LadderContactListener;
class WorldPositionComponent;

///A not-so-simple component which creates a physics box.
class SimpleBoxPhysics : public PhysicsComponent
{
    public:
        ///Creates a simple box
        /** \param opts Flags are defined in physics component **/
        SimpleBoxPhysics(unsigned int ID, sf::Vector2f size, float friction = 10, uint32 opts=0, std::shared_ptr<WorldPositionComponent> position = nullptr);
        void go(sf::Time, Entity* entity);
        bool onGround();
        unsigned int touchingGround();
        bool onLeft();
        unsigned int touchingLeft();
        bool onRight();
        unsigned int touchingRight();
        bool onTop();
        unsigned int touchingTop();
        bool onBody();
        unsigned int touchingBody();
        bool overLadder();

        std::vector<b2Vec2> getPath();
        virtual bool isPathClosed() {return true;}

        ComponentBase::listenerList getListeners();
        void HandleMessage(Events event, EventObj* message, Entity* entity);
    protected:
    private:
        FootContactListener* footListener;
        FootContactListener* headListener;
        FootContactListener* leftListener;
        FootContactListener* rightListener;
        FootContactListener* bodyListener;
        LadderContactListener* ladderListener;
        b2BodyDef physBodyDef;
        b2PolygonShape boxShape;
        b2FixtureDef boxFixtureDef;
        int screenHeight; //Need to convert Box2d to SFML coordinates
};

///Returns true when in contact with anything
class FootContactListener : public b2ContactListener
{
public:
    FootContactListener() : findID(0) {}
    FootContactListener(unsigned int findID) : findID(findID), onGroundNum(0), lastTouch(0) {}
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    bool onGround() {return onGroundNum>0;}
    unsigned int getTouching() {return lastTouch;}
private:
    unsigned int findID;
    int onGroundNum;
    unsigned int lastTouch;
};

///Returns true when in contact with anything of type "Ladder"
class LadderContactListener : public b2ContactListener
{
public:
    LadderContactListener() : origin(0), findID(0) {}
    LadderContactListener(unsigned int findID, PhysicsComponent* origin) : findID(findID), origin(origin), overLadderNum(0) {}
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    bool overLadder() {return overLadderNum>0;}
private:
    PhysicsComponent* origin;
    int overLadderNum;
    float currentGravity;
    unsigned int findID;
};

#endif // SIMPLEBOXPHYSICS_H
