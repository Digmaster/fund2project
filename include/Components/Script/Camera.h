#ifndef CAMERA_H
#define CAMERA_H

#include "Components/Script/ScriptComponent.h"
#include "Options.h"
#include <SFML/Graphics.hpp>

///Keeps the camera (mostly) centered on the target
class Camera : public ScriptComponent {
    public:
        /** Default constructor */
        Camera() : ScriptComponent() {}
        Camera(unsigned int ID, int xlimit, int ylimit);
        void go(sf::Time frameTime);
        sf::View getCamera() {return view;}
    protected:
    private:

        static int pixelsPerMeter;
        sf::View view;
        int screenHeight;
        int screenWidth;
        int xMax, yMax;
};


#endif // CAMERA_H
