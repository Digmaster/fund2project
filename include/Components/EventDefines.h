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
    FALL_END
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

#endif
