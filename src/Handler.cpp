
#include "engineModules/JamEngine.hpp"
#include "ASSETS_IDs.hpp"
#include "Handler.hpp"
#include "engineModules/AssetManager.hpp"
#include "enumObstacleDir.hpp"

Handler::~Handler(){

}

Handler::Handler() {
    WarningSprite.setTexture(AssetManager::Instance()->getTexture(WARNING));
    WarningSprite.setSize(220, 2);
    WarningSprite.setPosition(20, 0);
    WarningSprite.Visibility = false;
    JamEngine::Instance()->setDrawable_ZIndex(&WarningSprite, 8);
}

void Handler::ShowWarning( float hero_x, Zone& LeftArea, Zone& RightArea ) {
    if (hero_x > 240 && LeftArea.getObstacleDirection() == Top2Bottom) {
        WarningSprite.Visibility = true;
        WarningSprite.setPosition( 250, 270 );
    } else if (hero_x < 240 && RightArea.getObstacleDirection() == Bottom2Top) {
        WarningSprite.Visibility = true;
        WarningSprite.setPosition( 10, 0 );
    } else {
        WarningSprite.Visibility = false;
    }
}

