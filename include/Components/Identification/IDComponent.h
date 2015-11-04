#ifndef IDCOMPONENT_H
#define IDCOMPONENT_H

#include "Components/ComponentBase.h"

/// Component which contains information  useful to finding specific components
/** Such as Name, type **/
class IDComponent : public ComponentBase
{
    public:
        ///Constructor
        IDComponent(std::string = "", std::string = "", std::string = "");
        ///Sets the name. This is typically set in tiled
        void setName(std::string input) {name = input;}
        ///The type of object. This is the same value used to create the object (etc mob)
        void setType(std::string input) {type = input;}
        ///The faction of the object. This object will not hurt it's own kind
        void setFaction(std::string input) {faction = input;}
        ///Return name
        std::string getName() {return name;}
        ///Return type
        std::string getType() {return type;}
        ///Return faction
        std::string getFaction() {return faction;}
        virtual ~IDComponent();
        virtual void go(sf::Time, Entity* entity);
    protected:
    private:
        std::string name;
        std::string type;
        std::string faction;
};

#endif // IDCOMPONENT_H
