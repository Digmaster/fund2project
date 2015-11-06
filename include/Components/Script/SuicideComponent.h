#ifndef SUICIDECOMPONENT_H_H
#define SUICIDECOMPONENT_H_H

#include "Components/Script/ScriptComponent.h"

class SuicideComponent : public ScriptComponent
{
    public:
        SuicideComponent(sf::Time);
        virtual ~SuicideComponent();

        virtual void go(sf::Time frameTime, Entity* entity);
    protected:
    private:
        sf::Time timeToDie;
};

#endif // SUICIDECOMPONENT_H_H
