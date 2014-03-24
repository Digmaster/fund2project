#ifndef CAMERA_H
#define CAMERA_H

#include "Components/ComponentBase.h"
#include "Options.h"
#include <SFML/Graphics.hpp>


class Camera : public ComponentBase {
    public:
        /** Default constructor */
        Camera() {}
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
