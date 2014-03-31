#ifndef IDCOMPONENT_H
#define IDCOMPONENT_H

#include "Components/ComponentBase.h"

class IDComponent : public ComponentBase
{
    public:
        IDComponent() : ComponentBase() {}
        IDComponent(unsigned int, std::string = "", std::string = "");
        void setName(std::string input) {name = input;}
        void setType(std::string input) {type = input;}
        std::string getName() {return name;}
        std::string getType() {return type;}
        virtual ~IDComponent();
        virtual void go(sf::Time);
    protected:
    private:
        std::string name;
        std::string type;
};

#endif // IDCOMPONENT_H
