#ifndef KILLSCRIPT_H
#define KILLSCRIPT_H

#include "Components/Script/ScriptComponent.h"


class KillScript : public ScriptComponent
{
    public:
        KillScript(bool remove = true, int health = 10, sf::Time freq = sf::seconds(2));
        /** Default destructor */
        virtual ~KillScript();

        virtual void go(sf::Time frameTime, Entity* entity);
    protected:
    private:
        sf::Time frequency;
        sf::Time initFreq;
        int health;
        bool remove;
};

#endif // KILLSCRIPT_H
