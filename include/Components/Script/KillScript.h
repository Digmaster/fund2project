#ifndef KILLSCRIPT_H
#define KILLSCRIPT_H

#include "Components/Script/ScriptComponent.h"


class KillScript : public ScriptComponent
{
    public:
        /** Default constructor */
        KillScript();
        KillScript(unsigned int ID, int health = 10, sf::Time freq = sf::seconds(.5));
        /** Default destructor */
        virtual ~KillScript();

        virtual void go(sf::Time frameTime);
    protected:
    private:
        sf::Time frequency;
        int health;
};

#endif // KILLSCRIPT_H
