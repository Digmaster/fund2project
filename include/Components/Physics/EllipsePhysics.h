#ifndef ELLIPSEPHYSICS_H
#define ELLIPSEPHYSICS_H

#include "Components/ComponentManager.h"
#include "Components\Physics\PhysicsComponent.h"

#include "Components\Identification\IDComponent.h"

#include "Components/EventDefines.h"


class EllipsePhysics : public PhysicsComponent
{
    public:
        EllipsePhysics(unsigned int ID, sf::Vector2f size, float friction = 10, uint32 opts=0, std::shared_ptr<WorldPositionComponent> position = nullptr);
        void go(sf::Time, Entity* entity);

        std::vector<b2Vec2> getPath();
        virtual bool isPathClosed() {return true;}

        //ComponentBase::listenerList getListeners();
        //void HandleMessage(Events event, EventObj* message, Entity* entity);
    protected:
    private:
        void createEllipse(float x, float y, float friction, uint32 opts);
        void createCircle(float r, float friction, std::shared_ptr<WorldPositionComponent> position, uint32 opts);

        b2BodyDef physBodyDef;
        b2CircleShape circleShape;
        b2FixtureDef circleFixtureDef;

        //Used if path is needed
        float radius;
};

#endif // ELLIPSEPHYSICS_H
