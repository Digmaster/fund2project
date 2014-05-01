#ifndef MAINCHARSCRIPT_H
#define MAINCHARSCRIPT_H

#include "Components/Script/ScriptComponent.h"
#include <SFML/Graphics.hpp>

class MainCharScript : public ScriptComponent
{
    public:
        /** Default constructor */
        MainCharScript();
        MainCharScript(unsigned int ID);
        /** Default destructor */
        virtual ~MainCharScript();

        virtual void go(sf::Time frameTime);
    protected:
    private:
        sf::Time deathCountDown;
};

#endif // MAINCHARSCRIPT_H
