#include "Components/Script/Camera.h"
#include "Components/ComponentManager.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Positional/WorldPositionComponent.h"
#include "Rendering/RenderEngine.h"
#include "Components/Target/TargetComponent.h"
#include "Components/Entity.h"


Camera::Camera(int xlimit, int ylimit) : ScriptComponent() {
	xMax = (xlimit*pixelsPerMeter) - (pixelsPerMeter/2);
	yMax = (ylimit*pixelsPerMeter) - (pixelsPerMeter/2);
}

int Camera::pixelsPerMeter = atoi(Options::instance().get("pixels_per_meter").c_str());

void Camera::go(sf::Time frameTime, Entity* entity) {
    TargetComponent* tarComp = entity->target;
    if(tarComp != NULL) {
        const Entity* target = (*compMan)[tarComp->getTarget()];
        if(target!=NULL)
        {
            //PhysicsComponent* phys = compMan->physSym.getComponent(tarComp->getTarget());
            WorldPositionComponent* pos = target->position;
            if(pos!=NULL) {
                screenWidth = rendEng->window.getSize().x;
                screenHeight = rendEng->window.getSize().y;
                int pos_x = pos->getPosition().x;
                int pos_y = pos->getPosition().y;
                // HACK (Thomas Luppi#5#03/25/14): Changed float to int to remove those weird line errors. Probably a better way to do it.

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
                sf::Listener::setPosition(pos->getPosition().x, 0, pos->getPosition().y);

                rendEng->centerViews(getCamera().getCenter());
            }
        }
    }
}

