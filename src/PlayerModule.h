#pragma once
#include "Module.h"
#include <iostream>
#include "Player.h"
#include "TileMap.h"
#include "Constants.h"


// forward declare Engine so we can use Engine& in signatures
class Engine;

struct PlayerModule : Module {
    Player* player = nullptr;
    TileMap* tileMap = nullptr;
    Camera* camera = nullptr;

    // **Declare** but do *not* define these in the header:
    bool   init(Engine* E)            override;
    void   update(Engine& E, float dt)override;
    void   render(Engine& E)          override;
    void   shutdown(Engine& E)        override;

    // Wiring
    void setPlayer(Player* p) { player = p; }
    Player* getPlayer() { return player; }
    void setTileMap(TileMap* m) { tileMap = m; }
    void setCamera(Camera* c) { camera = c; }
};