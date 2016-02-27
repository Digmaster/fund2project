#ifndef GUILOADER_H
#define GUILOADER_H

#include <string>
#include "Rendering/TextureManager.h"
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include "GameEngine.h"

class GuiLoader
{
    public:
        GuiLoader();

        //! Load a GUI file
        /** Takes in a standardized xml file **/
        void load(std::string guiFile, GameEngine* eng);

    protected:
    private:
        TextureManager* texMan;
};

#endif // GUILOADER_H
