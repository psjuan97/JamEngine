
#include "engineModules/JamEngine.hpp"
#include "ASSETS_IDs.hpp"
#include "Handler.hpp"
#include "engineModules/AssetManager.hpp"

Handler::~Handler(){

}

Handler::Handler() {
    WarningSprite.setTexture(AssetManager::Instance()->getTexture(WARNING));
    WarningSprite.setSize(220, 2);
    WarningSprite.setPosition(20, 0);
    WarningSprite.Visibility = true;
    JamEngine::Instance()->setDrawable_ZIndex(&WarningSprite, 8);
}

void Handler::handleEvents() {
    // CONTROLAR EL WARNIGN
    ShowWarning();
}

/// ZONA - DIRECCION - 
void Handler::ShowWarning() {
    WarningSprite.setPosition( 10, 0 );
}