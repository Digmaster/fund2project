#include "Components/Script/MainCharScript.h"

#include "Components/Stats/StatsComponent.h"
#include "Components/ComponentManager.h"
#include "GameEngine.h"

MainCharScript::MainCharScript() : MainCharScript(0)
{

}

MainCharScript::MainCharScript(unsigned int ID, bool endGame) : ScriptComponent(ID)
{
    mainChar = endGame;
    deathCountDown = sf::seconds(5);
}

MainCharScript::~MainCharScript()
{
    //dtor
}

void MainCharScript::go(sf::Time frameTime)
{
    StatsComponent* stats = compMan->statSym.getComponent(getID());
    if(stats) {
        if(stats->isDead()) {
            compMan->moveSym.removeComponent(getID()); //Remove movement
            compMan->inputSym.removeComponent(getID()); //input
            compMan->physSym.removeComponent(getID()); //physics
            deathCountDown -= frameTime; //Give everything time to play death animations and whatnot
            if(deathCountDown <= sf::seconds(0)) {
                compMan->audioSym.removeComponent(getID());
                compMan->idSym.removeComponent(getID());
                compMan->posSym.removeComponent(getID());
                compMan->rendSym.removeComponent(getID());
                compMan->statSym.removeComponent(getID());
                compMan->targetSym.removeComponent(getID());
                compMan->scriptSym.removeComponent(getID()); //Oh god, remove self
                if(mainChar) eng->playerDied();
            }
        }
    }
}
