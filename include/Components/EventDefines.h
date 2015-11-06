#ifndef EVENTDEFINES_H
#define EVENTDEFINES_H

class Entity;

enum Events {
    HEALTH_CHANGE,
    DEATH,
    CLIMBING_START,
    CLIMBING_END,
    JUMP,
    FALL_START,
    FALL_END,
    COLLISION
};

struct EventObj
{
};

struct HealthChange : public EventObj
{
    int ammount;
    int newHealth;
    int prevHealth;
    Entity* causer;
    HealthChange(int a, int n, int p, Entity* c) : ammount(a), newHealth(n), prevHealth(p), causer(c) {}
};

struct Collision : public EventObj
{
    int side;
    Entity* entity;
    float speed;
    Collision(int s, Entity* e, float s1) : side(s), entity(e), speed(s1) {}
    enum Side : int {
        SIDE_TOP,
        SIDE_BOTTOM,
        SIDE_LEFT,
        SIDE_RIGHT,
        SIDE_BODY
    };
};

#endif
