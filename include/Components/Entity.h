#ifndef ENTITY_H
#define ENTITY_H

#include<list>
#include<memory>

class AudioComponent;
class RenderComponent;
class IDComponent;
class InputComponent;
class MovementComponent;
class PhysicsComponent;
class WorldPositionComponent;
class StatsComponent;
class TargetComponent;
class ScriptComponent;

/// Contains all the components an entity has
class Entity
{
    public:
        Entity(int ID);
        virtual ~Entity();

        AudioComponent* audio;
        RenderComponent* render;
        IDComponent* identification;
        InputComponent* input;
        MovementComponent* movement;
        PhysicsComponent* physics;
        WorldPositionComponent* position;
        StatsComponent* stats;
        TargetComponent* target;
        std::list<ScriptComponent*> scripts;

        int getID() {return _ID;}

        void setDelete() {_delete = true;}
        int isDeleted() {return _delete;}
    protected:
        int _ID;
        bool _delete;
    private:
};

#endif // ENTITY_H
