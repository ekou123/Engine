#include <SDL3/SDL.h>
#include <iostream>
#include <algorithm>
#include "TileMap.h"
#include "TilesetLoader.h"
#include "Camera.h"
#include"Constants.h"
#include "Player.h"
#include "BlockRegistry.h"
#include "Engine.h"
#include "WorldModule.h"
#include "PlayerModule.h"
#include "CameraModule.h"
#include "GravityComponent.h"
#include "MapComponent.h"
#include "RenderModule.h"

// main.cpp (Game)
int main() {
    Engine engine;

    auto worldMod = std::make_unique<WorldModule>();
    auto playerMod = std::make_unique<PlayerModule>();
    auto cameraMod = std::make_unique<CameraModule>();
    auto renderMod = std::make_unique<RenderModule>();

    //Player player(WINDOW_W / 2.0f, WINDOW_H / 2.0f, worldMod->tileSet);
    Player player(0,0, worldMod->tileSet);

    // 1) Register the player with the PlayerModule
    playerMod->setPlayer(&player);
    player.setCurrentMap(worldMod->tileSet);

    /*player.addComponent<PositionComponent>();
    player.addComponent<GravityComponent>(9.8f);
    player.addComponent<MapComponent>(worldMod->tileSet);
    player.getComponent<GravityComponent>()->setOwner(&player);*/


    // 1) Inject the *real* camera & player
    worldMod->setCamera(&cameraMod->cam);
    playerMod->setTileMap(worldMod->tileSet);
    cameraMod->setPlayerModule(playerMod.get());

    // 2) **This is the critical line**: give RenderModule the WorldModule's map
    renderMod->setWorld(worldMod->tileSet);
    renderMod->setPlayer(playerMod->getPlayer());
    renderMod->setCamera(&cameraMod->cam); 
    playerMod->setCamera(&cameraMod->cam); 


    playerMod->getPlayer()->setCamera(&cameraMod->cam);
    engine.registerPlayer(playerMod->getPlayer());
    
    


    // 3) Register in order
    engine.registerModule(std::move(worldMod));
    engine.registerModule(std::move(playerMod));
    engine.registerModule(std::move(cameraMod));
    engine.registerModule(std::move(renderMod));

    if (!engine.init("TerrariaEngine", WINDOW_W, WINDOW_H)) return 1;
    engine.run();                                                                                                       
    engine.shutdown();
    return 0;
}
