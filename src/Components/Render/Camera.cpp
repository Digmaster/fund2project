#include "Components/Render/Camera.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"


Camera::Camera(unsigned int ID, int xlimit, int ylimit) : ComponentBase(ID) {
    compMan->etcSym.addComponent(this);
    screenWidth = atoi(Options::instance().get("screen_width").c_str());
	screenHeight = atoi(Options::instance().get("screen_height").c_str());
	xMax = (xlimit*pixelsPerMeter) - (pixelsPerMeter/2);
	yMax = (ylimit*pixelsPerMeter) - (pixelsPerMeter/2);
}

int Camera::pixelsPerMeter = atoi(Options::instance().get("pixels_per_meter").c_str());

void Camera::go(sf::Time frameTime) {
    PhysicsComponent* phys = compMan->physSym.getComponent(getID());
    if(phys!=NULL) {

        float pos_x= phys->getBody()->GetWorldCenter().x*pixelsPerMeter;
        float pos_y= -phys->getBody()->GetWorldCenter().y*pixelsPerMeter;

        // The view limits are suppose to depend on the limits of the tile map not on the screen but for now works
        if(pos_x < screenWidth/2){    //Limits the View so that it doesnt follow to the left if the character moves there
            pos_x = screenWidth/2;
        }
        else if(pos_x > xMax - (screenWidth/2)){
            pos_x = xMax - (screenWidth/2);
        }

        if( pos_y < screenHeight/2){
            pos_y = screenHeight/2;
        }
        else if(pos_y > yMax - (screenHeight/2)){ //Limits the view so that if the Hero falls then the View does not follow under the ground
            pos_y = yMax - (screenHeight/2);
        }

        view.setCenter(pos_x, pos_y);
    }
}

