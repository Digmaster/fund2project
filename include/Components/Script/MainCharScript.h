#ifndef MAINCHARSCRIPT_H
#define MAINCHARSCRIPT_H

#include "Components/Script/ScriptComponent.h"
#include <SFML/Graphics.hpp>

class MainCharScript : public ScriptComponent
{
    public:

        MainCharScript(bool endGame = false, sf::Time=sf::seconds(0));
        /** Default destructor */
        virtual ~MainCharScript();

        virtual void go(sf::Time frameTime, Entity* entity);
    protected:
    private:
        sf::Time deathCountDown;
        bool mainChar;
};

#endif // MAINCHARSCRIPT_H
