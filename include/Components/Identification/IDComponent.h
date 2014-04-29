#ifndef IDCOMPONENT_H
#define IDCOMPONENT_H

#include "Components/ComponentBase.h"

/// Component which contains information  useful to finding specific components
/** Such as Name, type **/
class IDComponent : public ComponentBase
{
    public:
        ///Default constructor
        IDComponent() : ComponentBase() {}
        ///Constructor
        IDComponent(unsigned int, std::string = "", std::string = "");
        ///Sets the name. This is typically set in tiled
        void setName(std::string input) {name = input;}
        ///The type of object. This is the same value used to create the object (etc mob)
        void setType(std::string input) {type = input;}
        ///Return name
        std::string getName() {return name;}
        ///Return type
        std::string getType() {return type;}
        virtual ~IDComponent();
        virtual void go(sf::Time);
    protected:
    private:
        std::string name;
        std::string type;
};

#endif // IDCOMPONENT_H
