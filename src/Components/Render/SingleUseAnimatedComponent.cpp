#include "Components/Render/SingleUseAnimatedComponent.h"
#include "Rendering/SpriteManager.h"
#include "Components/ComponentManager.h"

SingleUseAnimatedComponent::SingleUseAnimatedComponent(std::string spriteName, std::string animation, bool DestroyOnFinish)
{
    SpriteManager spriteMan;
    setSprite(spriteMan.getSprite(spriteName));
    sprite.setAnimation(animation);
    sprite.setLooped(!DestroyOnFinish);
    sprite.play();
}

void SingleUseAnimatedComponent::go(sf::Time fps, Entity* entity) {

    //If the sprite isn't playing, DESTROY EVERYTHING!
    if(!sprite.isPlaying())
        compMan->removeEntity(entity->getID());
    else
        AnimatedComponent::go(fps, entity);
}
