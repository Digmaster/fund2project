#ifndef IDCOMPONENT_H
#define IDCOMPONENT_H

#include "Components/ComponentBase.h"


class IDComponent : public ComponentBase
{
    public:
        IDComponent() : ComponentBase() {}
        IDComponent(unsigned int, std::string);
        void setName(std::string input) {name = input;}
        std::string getName() {return name;}
        virtual ~IDComponent();
        virtual void go(sf::Time);
    protected:
    private:
        std::string name;
};

#endif // IDCOMPONENT_H
